cmake_minimum_required(VERSION 3.8)
project(Reversi)

add_subdirectory(gtest/googletest)
include_directories(src)
include_directories(include)
include_directories(gtest/googletest/include)
include_directories(gtest/googlemock/include)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -pthread")

set(SOURCE_FILES
        src/client/src/Board.cpp
        src/client/include/Board.h
        src/client/src/Game.cpp
        src/client/include/Game.h
        src/client/include/BoardLogic.h
        src/client/src/BoardLogic.cpp
        src/client/include/GameLogic.h
        src/client/src/GameLogic.cpp
        src/client/src/Player.cpp
        src/client/include/Player.h
        src/client/src/LocalPlayer.cpp
        src/client/include/LocalPlayer.h
        src/client/src/ConsoleDisplay.cpp
        src/client/include/ConsoleDisplay.h
        src/client/src/Display.cpp
        src/client/include/Display.h
        src/client/src/Cell.cpp
        src/client/include/Cell.h
        src/client/src/Coordinate.cpp
        src/client/include/Coordinate.h
        src/client/src/ScoreTracker.cpp
        src/client/include/ScoreTracker.h
        src/client/src/Counter.cpp
        src/client/include/Counter.h
        src/client/src/AIPlayer.cpp
        src/client/include/AIPlayer.h
        src/client/src/Move.cpp
        src/client/include/Move.h
        src/client/include/RemotePlayer.h
        src/client/src/RemotePlayer.cpp
        src/client/src/Menu.cpp
        src/client/include/Menu.h
        src/client/src/MenuItem.cpp
        src/client/include/MenuItem.h
        src/client/src/LocalVersusLocalChoice.cpp
        src/client/include/LocalVersusLocalChoice.h
        src/client/src/LocalVersusAIChoice.cpp
        src/client/include/LocalVersusAIChoice.h
        src/client/src/LocalVersusRemoteChoice.cpp
        src/client/include/LocalVersusRemoteChoice.h
        src/client/src/TwoPlayers.cpp
        src/client/include/TwoPlayers.h
        src/client/src/StartNewRemoteGameTask.cpp
        src/client/include/StartNewRemoteGameTask.h
        src/client/src/JoinToGameTask.cpp
        src/client/include/JoinToGameTask.h
        src/client/include/custom_strings.h
        src/client/src/ShowAvailableGamesTask.cpp
        src/client/include/ShowAvailableGamesTask.h
        src/client/src/QuitGameChoice.cpp
        src/client/include/QuitGameChoice.h
        src/client/src/CloseSelfSocketTask.cpp
        src/client/include/CloseSelfSocketTask.h
        src/client/src/CloseOtherSocketTask.cpp
        src/client/include/CloseOtherSocketTask.h)

set(TEST_FILES
        src/client/tests/board_test.cpp
        src/client/tests/ai_test.cpp
        src/client/tests/board_logic_test.cpp)

set(SERVER_FILES
        src/server/include/Server.h
        src/server/src/Server.cpp
        src/server/src/CommandManager.cpp
        src/server/include/CommandManager.h
        src/server/src/Command.cpp
        src/server/include/Command.h
        src/server/src/StartCommand.cpp
        src/server/include/StartCommand.h
        src/server/include/AvailableGames.h
        src/server/src/AvailableGames.cpp
        src/server/include/RunningGames.h
        src/server/src/RunningGames.cpp
        src/server/src/ListGamesCommand.cpp
        src/server/include/ListGamesCommand.h
        src/server/src/JoinCommand.cpp
        src/server/include/JoinCommand.h
        src/server/src/CloseCommand.cpp
        src/server/include/CloseCommand.h)

add_executable(client ${SOURCE_FILES} src/client/src/client_main.cpp)

add_executable(testing ${TEST_FILES} ${SOURCE_FILES}
        src/client/tests/gtest_main.cpp)

add_executable(server ${SERVER_FILES} src/server/src/server_main.cpp)

target_link_libraries(client gtest gtest_main)
target_link_libraries(testing gtest gtest_main)