#pragma once
#include <pgt/utils/containers/Queue.h>
#include <thread>
#include <mutex>
#include "SharedDataStructs.h"
#include <pgt/graphics/plattform/opengl/voxel/models/VoxelModelAsync.h>
namespace pgt {
    template <bool LOAD>
    class AsyncVoxelModelUpdater {
      public:
      private:
        struct model_update_request {
            VoxelModelAsync* model;
            update_parameters* params;
        };

      private:
        std::thread** _threads;
        std::atomic<bool> _running;
        const int _thread_count;
        std::mutex* _priority_locks[PRIORITY_COUNT];
        pgt::Queue<model_update_request>* _priorities[PRIORITY_COUNT];

      public:
        static int getThreadCountSuggestion()
        {
            int tc = std::thread::hardware_concurrency();
            tc = pgt::clamp(tc, 1, 4);
            return tc;
        }
        AsyncVoxelModelUpdater(int thread_count) : _thread_count(thread_count)
        {
            _running = false;
            _threads = new std::thread*[_thread_count];
            for (int i = PRIORITY_FIRST; i < PRIORITY_COUNT; i++) {
                _priorities[i] = new pgt::Queue<model_update_request>();
                _priority_locks[i] = new std::mutex();
            }
        }
        ~AsyncVoxelModelUpdater()
        {
            delete[] _threads;
            for (int i = PRIORITY_FIRST; i < PRIORITY_COUNT; i++) {
                delete _priorities[i];
                delete _priority_locks[i];
            }
        }

      public:
        int getThreadCount()
        {
            return _thread_count;
        }
        void requestUpdate(UpdatePriority priority, VoxelModelAsync* model,
                           update_parameters* params)
        {
            if (LOAD) {
                model->registerLoadRequest();
            }
            else {
                model->registerUpdateRequest();
            }
            model_update_request request = model_update_request();
            request.model = model;
            request.params = params;

            _priority_locks[priority]->lock();
            _priorities[priority]->push_back(request);
            _priority_locks[priority]->unlock();

            return;
        }

        void start()
        {
            _running = true;
            for (int i = 0; i < _thread_count; i++) {
                _threads[i] = new std::thread(
                    &AsyncVoxelModelUpdater::updateFunc, this, i);
            }
        }

        void stop()
        {
            _running = false;
            for (int i = 0; i < _thread_count; i++) {
                _threads[i]->join();
                delete _threads[i];
            }
        }

      private:
        bool performUpdate(int thread_id, model_update_request& r)
        {
            if (LOAD) {
                return r.model->carryOutAsyncModelLoad(thread_id, r.params);
            }
            else {
                return r.model->carryOutAsyncModelUpdate(thread_id, r.params);
            }
        }
        void updateFunc(int thread_id)
        {
            model_update_request r;
            while (_running) {
                getNextRequest(r);
                while (_running && !performUpdate(thread_id, r)) {
                    std::this_thread::yield();
                }
            }
        }

        void getNextRequest(model_update_request& r)
        {
            while (_running) {
                for (int i = PRIORITY_FIRST; i < PRIORITY_COUNT; i++) {
                    _priority_locks[i]->lock();
                    if (_priorities[i]->size() > 0) {
                        r = _priorities[i]->front();
                        _priorities[i]->pop_front();
                        _priority_locks[i]->unlock();
                        return;
                    }
                    _priority_locks[i]->unlock();
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }
    };
}