#pragma once
#include "pgt/window/plattform/target.h"
namespace pgt {
    class GameWindow : public Window {
    private:
        int _tick_of_second, _frames_this_second;
        int _fps, _tps, _target_tps;
        Stopwatch _update_timer;
        Stopwatch _time_since_last_tick;

    public:
        GameWindow(const window_creation_hints& hints);

    public:
        int getFPS() const;
        int getTPS() const;
        int getTargetTPS() const;
        int getCurrentTick() const;
        float getTickPercentage() const;
        int getCurrentFrame() const;

        bool prefersEventBased() const override;

    private:
        void internal_update() override;
        void tick();
    };
}