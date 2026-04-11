//
// Created by 李政翰 on 2026/4/11.
//
#include "Board/BoardPresets.hpp"

BoardLayout BoardPresets::GetLayout(BoardTypes type) {
    BoardLayout layout;

    switch (type) {
        case BoardTypes::DAY_SINGLE_ROW:
            layout.rowCenters = {
                -28.0f
        };
            layout.colCenters = {
                -219.0f,
                -139.0f,
                -56.0f,
                29.0f,
                102.0f,
                184.0f,
                263.0f,
                339.0f,
                428.0f
            };
            break;

        case BoardTypes::DAY_MIDDLE_3_ROW:
            layout.rowCenters = {
                70.0f,
                -28.0f,
                -126.0f
        };
            layout.colCenters = {
                -219.0f,
                -139.0f,
                -56.0f,
                29.0f,
                102.0f,
                184.0f,
                263.0f,
                339.0f,
                428.0f
            };
            break;

        case BoardTypes::DAY_FULL_5_ROW:
            layout.rowCenters = {
                170.0f,
                70.0f,
                -28.0f,
                -126.0f,
                -222.0f
        };
            layout.colCenters = {
                -219.0f,
                -139.0f,
                -56.0f,
                29.0f,
                102.0f,
                184.0f,
                263.0f,
                339.0f,
                428.0f
            };
            break;
    }

    return layout;
}

