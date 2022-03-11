#include <iostream>
#include <unistd.h>

enum class ElevatorState {
    UP,
    DOWN,
    STOP
};

enum class DoorState {
    OPEN,
    CLOSE
};

class Elevator {
public:
    Elevator() : state_(ElevatorState::STOP), cur_floor_(1), speed_(1000000), door_state_(DoorState::CLOSE) {}
    void Move(int destination, ElevatorState direction) {
        PrintCurrentFloor();
        SetState(direction);
        switch(state_) {
            case ElevatorState::UP :
                MoveUP(destination);
                break;
            case ElevatorState::DOWN :
                MoveDown(destination);
                break;
        }
        std::cout << "ding!" << std::endl;
    }

    void Call(int user_floor) {
        if(user_floor == cur_floor_) {
            SetDoorState(DoorState::OPEN);
            return;
        }
        else if(user_floor < cur_floor_) {
            Move(user_floor, ElevatorState::DOWN);
        }
        else {
            Move(user_floor, ElevatorState::UP);
        }
    }

    void MoveUP(int destination) {
        for(int i = cur_floor_; i < destination; i++) {
            usleep(speed_);
            ++cur_floor_;
            PrintCurrentFloor();
        }
        SetState(ElevatorState::STOP);
    }

    void MoveDown(int destination) {
        for(int i = cur_floor_; i > destination; i--) {
            usleep(speed_);
            --cur_floor_;
            std::cout << cur_floor_ << std::endl;
        }
        SetState(ElevatorState::STOP);
    }

    void PrintCurrentFloor() {
        std::cout << cur_floor_ << std::endl;
    }
    void SetState(ElevatorState state) {
        state_ = state;
    }

    void SetDoorState(DoorState state) {
        door_state_ = state;
    }

private:
    ElevatorState state_;
    int cur_floor_;
    unsigned int speed_;
    DoorState door_state_;
};