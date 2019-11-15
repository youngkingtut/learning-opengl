#pragma once


class PausedControlState {
public:
    void setPausePress(bool status);
    void setPauseRelease(bool status);

    bool getPausePress() const;
    bool getPauseRelease() const;
private:
    bool pausePress{false};
    bool pauseRelease{false};
};


