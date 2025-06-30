#include "assistant.h"

namespace yume {

    void zmienLinieWPliku(const std::string& proj_path);

	void runAssistant() {
        std::cout << "Asisstant is running...\n";

        std::filesystem::path current_path = std::filesystem::current_path();
        std::cout << "Project path: " << current_path << '\n';

#ifdef _WIN32
        // Windows
        system("cd res/assistant && make");
#else
        // Linux / macOS
        system("make -C res/assistant");
#endif
	}
}