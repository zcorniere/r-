#ifndef PLAYER_SHIP_CONTROLLER_HPP
#define PLAYER_SHIP_CONTROLLER_HPP

class PlayerShipController {
    unsigned m_player_id;
    float m_speed;
public:
    bool moovingUp;
    bool moovingDown;
    bool moovingRight;
    bool moovingLeft;
    bool firing;
    unsigned m_moovingUp_ticks = 0;
    unsigned m_moovingDown_ticks = 0;
    PlayerShipController(unsigned player_id, float speed);
    unsigned getPlayerId() const;
    float getSpeed() const;
};

#endif
