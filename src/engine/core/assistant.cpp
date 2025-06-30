#include "assistant.h"

namespace yume {

    void zmienLinieWPliku(const std::string& proj_path);

	void runAssistant() {
        std::cout << "Asisstant is running...\n";

        std::filesystem::path executable_path = std::filesystem::current_path();
        std::cout << "Executable path: " << executable_path << '\n';
        std::cout << "If this is a project using YUME, the project path includes everything up to and including the YUME folder. \n";
        std::cout << "WARNING - If the assistant doesn’t work correctly, please check whether the proj_dir in assistant.py is correct. \n";

#ifdef _WIN32
        // Windows
        system("cd res/assistant && make");
#else
        // Linux / macOS
        system("make -C res/assistant");
#endif
	}
}