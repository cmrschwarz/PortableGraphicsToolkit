#include "GameWindow.h"

namespace pgt {

    void GameWindow::internal_update()
    {
        // never falling behind more than one tick
        float time_per_tick = 1000.0f / _target_tps;
        int tc = 0;
        double elapsed = _update_timer.getElapsedTimeMillis();
        while (elapsed >= _tick_of_second * time_per_tick) {
            tick();
            tc++;
            elapsed = _update_timer.getElapsedTimeMillis();
            if (_tick_of_second == _target_tps) {
                _update_timer.advanceStartByMillis(1000);
                _fps = _frames_this_second;
                _tps = _tick_of_second;
                _tick_of_second = 0;
                _frames_this_second = 0;
            }
        }
        if (tc > 2) PGT_LOG_WARN("MULTITICK: %i", tc);
        _frames_this_second++;
        Window::internal_update();
    }

    void GameWindow::tick()
    {
        raiseOnTick();
        _time_since_last_tick.setStart();
        _tick_of_second++;
        wipeKeyPresses();
    }

    GameWindow::GameWindow(const window_creation_hints& hints)
        : Window(hints),
          _tick_of_second(0),
          _frames_this_second(0),
          _fps(0),
          _tps(0)
    {
        _target_tps = hints.tps;
        _update_timer.setStart();
        _time_since_last_tick.setStart();
    }

    int GameWindow::getFPS() const
    {
        return _fps;
    }

    int GameWindow::getTPS() const
    {
        return _tps;
    }

    int GameWindow::getTargetTPS() const
    {
        return _target_tps;
    }

    int GameWindow::getCurrentTick() const
    {
        return _tick_of_second;
    }

    float GameWindow::getTickPercentage() const
    {
#if 0
		float time_per_tick = 1000.0f / _target_tps;
		float percentage = (float)(_time_since_last_tick.getElapsedTimeMillis()) / time_per_tick;
		percentage = pgt::clamp(percentage, 0.0f, 1.0f);
		PGT_LOG_INFO("%f", percentage);
		return percentage;
#else
        // ITS MAGIC! DONT TOUCH
        //(Exponential Decay function for smooth movement interpolation
        // between
        // frames)
        float springiness = 42;  // can be tweaked
        float d =
            1.0f -
            std::exp(std::log(0.5f) * springiness *
                     (float)_time_since_last_tick.getElapsedTimeSeconds());
        return d;
#endif
    }

    int GameWindow::getCurrentFrame() const
    {
        return _frames_this_second;
    }

    bool GameWindow::prefersEventBased() const
    {
        return false;
    }
}  // namespace pgt
