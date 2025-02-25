#include "nes/Emulator.h"
#include "utility/Log.h"
#include <string>
#include <sstream>

using namespace utility;

namespace nes
{
	void parseControllerConf(const std::string &filepath,
							 std::vector<sf::Keyboard::Key> &p1,
							 std::vector<sf::Keyboard::Key> &p2);
}

int main(int argc, char **argv)
{
	std::ofstream logFile("nes_rl.log"), cpuTraceFile;
	utility::TeeStream logTee(logFile, std::cout);

	if (logFile.is_open() && logFile.good())
		Log::get().setLogStream(logTee);
	else
		Log::get().setLogStream(std::cout);

	Log::get().setLevel(Info);

	std::string path;

	//Default keybindings
	std::vector<sf::Keyboard::Key> p1{sf::Keyboard::X, sf::Keyboard::Z, sf::Keyboard::RShift, sf::Keyboard::Return,
									  sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right},
			p2{sf::Keyboard::Numpad5, sf::Keyboard::Numpad6, sf::Keyboard::Numpad8, sf::Keyboard::Numpad9,
			   sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D};
	nes::Emulator emulator;

	for (int i = 1; i < argc; ++i)
	{
		std::string arg(argv[i]);
		if (arg == "-h" || arg == "--help")
		{
			std::cout << "NES4RL is a simple NES emulator.\n"
					  << "It can run off .nes images.\n"
					  << "Set keybindings with keybindings.conf\n\n"
					  << "Usage: NES4RL [options] rom-path\n\n"
					  << "Options:\n"
					  << "-h, --help             Print this help text and exit\n"
					  << "-s, --scale            Set video scale. Default: 2.\n"
					  << "                       Scale of 1 corresponds to " << nes::NESVideoWidth << "x"
					  << nes::NESVideoHeight << std::endl
					  << "-w, --width            Set the width of the emulation screen (height is\n"
					  << "                       set automatically to fit the aspect ratio)\n"
					  << "-H, --height           Set the height of the emulation screen (width is\n"
					  << "                       set automatically to fit the aspect ratio)\n"
					  << "                       This option is mutually exclusive to --width\n"
					  << std::endl;
			return 0;
		} else if (std::strcmp(argv[i], "--log-cpu") == 0)
		{
			Log::get().setLevel(CpuTrace);
			cpuTraceFile.open("nes.cpudump");
			Log::get().setCpuTraceStream(cpuTraceFile);
			LOG(Info) << "CPU logging set." << std::endl;
		} else if (std::strcmp(argv[i], "-s") == 0 || std::strcmp(argv[i], "--scale") == 0)
		{
			float scale;
			std::stringstream ss;
			if (i + 1 < argc && ss << argv[i + 1] && ss >> scale)
				emulator.setVideoScale(scale);
			else LOG(Error) << "Setting scale from argument failed" << std::endl;
			++i;
		} else if (std::strcmp(argv[i], "-w") == 0 || std::strcmp(argv[i], "--width") == 0)
		{
			int width;
			std::stringstream ss;
			if (i + 1 < argc && ss << argv[i + 1] && ss >> width)
				emulator.setVideoWidth(width);
			else LOG(Error) << "Setting width from argument failed" << std::endl;
			++i;
		} else if (std::strcmp(argv[i], "-H") == 0 || std::strcmp(argv[i], "--height") == 0)
		{
			int height;
			std::stringstream ss;
			if (i + 1 < argc && ss << argv[i + 1] && ss >> height)
				emulator.setVideoHeight(height);
			else LOG(Error) << "Setting height from argument failed" << std::endl;
			++i;
		} else if (argv[i][0] != '-')
			path = argv[i];
		else
			std::cerr << "Unrecognized argument: " << argv[i] << std::endl;
	}

	if (path.empty())
	{
		std::cout << "Argument required: ROM path" << std::endl;
		return 1;
	}

	nes::parseControllerConf("keybindings.conf", p1, p2);
	emulator.setKeys(p1, p2);
	emulator.run(path);
	return 0;
}
