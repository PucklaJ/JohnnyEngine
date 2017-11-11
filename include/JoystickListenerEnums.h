#ifndef JOYSTICKLISTENERENUMS_H
#define JOYSTICKLISTENERENUMS_H

namespace Johnny
{
    /*! \brief A enum which consists of all Buttons of a controller
     *
     */
    enum Buttons
    {
        UP = 11,
        DOWN = 12,
        LEFT = 13,
        RIGHT = 14,
        START = 6,
        SELECT = 4,
        L3 = 7,
        R3 = 8,
        L1 = 9,
        R1 = 10,
        CROSS = 0,
        CIRCLE = 1,
        SQUARE = 2,
        TRIANGLE = 3,
        BACK=SELECT,
        LS=L3,
        RS=R3,
        LB=L1,
        RB=R1,
        A=CROSS,
        B=CIRCLE,
        X=SQUARE,
        Y=TRIANGLE
    };
	 
    /*!\brief A enum which consists of the sticks and triggers of a controller
     *
     */
    enum Axis
    {
        LEFT_STICK_X=0,
        LEFT_STICK_Y=1,
        RIGHT_STICK_X=2,
        RIGHT_STICK_Y=3,
        L2=4,
        R2=5,
        LT=L2,
        RT=R2
    };
}

#endif

