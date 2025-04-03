#include "api/GameController.h"
#include "game/Game.h"

void printUsage(const char *progName) {
    std::cout << "Usage: " << progName
            << " -mode <api|keyboard> [-port <port>]"
            << std::endl;
}

int main(int argc, char **argv) {
    // Check for minimum required arguments.
    if (argc < 3) {
        printUsage(argv[0]);
        return 1;
    }

    std::string mode;
    unsigned short port = 8000; // Default port for API mode.

    // Parse command-line arguments.
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-mode") {
            if (i + 1 < argc) {
                mode = argv[++i];
            } else {
                std::cerr << "Error: Missing value for -mode." << std::endl;
                printUsage(argv[0]);
                return 1;
            }
        } else if (arg == "-port") {
            if (i + 1 < argc) {
                try {
                    port = static_cast<unsigned short>(std::stoi(argv[++i]));
                } catch (const std::exception &e) {
                    std::cerr << "Error: Invalid port number: " << argv[i] << std::endl;
                    printUsage(argv[0]);
                    return 1;
                }
            } else {
                std::cerr << "Error: Missing value for -port." << std::endl;
                printUsage(argv[0]);
                return 1;
            }
        } else {
            std::cerr << "Error: Unknown argument: " << arg << std::endl;
            printUsage(argv[0]);
            return 1;
        }
    }

    // Validate mode.
    if (mode != "api" && mode != "keyboard") {
        std::cerr << "Error: Mode must be either 'api' or 'keyboard'." << std::endl;
        printUsage(argv[0]);
        return 1;
    }

    // Execute based on the chosen mode.
    if (mode == "api") {
        CommandQueue *commandQueue = new CommandQueue();
        GameController gameController{commandQueue};
        gameController.runServer(port); // Use specified port.

        Game game{{new ApiEventManager(commandQueue), new KeyboardEventManager()}};
        game.start();
    } else if (mode == "keyboard") {
        Game game{new KeyboardEventManager()};
        game.start();
    }

    return 0;
}
