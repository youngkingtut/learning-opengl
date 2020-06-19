#pragma once


class GameOverControlState {
public:
    void setReset(bool r);
    bool getReset() const;
private:
    bool reset{false};
};


