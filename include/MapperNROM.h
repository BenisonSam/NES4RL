#ifndef MAPPERNROM_H
#define MAPPERNROM_H

#include "Mapper.h"

namespace nes
{
	class MapperNROM : public Mapper
	{
	public:
		explicit MapperNROM(Cartridge &cart);

		void writePRG(Address addr, Byte value) override;

		Byte readPRG(Address addr) override;

		const Byte *getPagePtr(Address addr) override;

		Byte readCHR(Address addr) override;

		void writeCHR(Address addr, Byte value) override;

	private:
		bool m_oneBank;
		bool m_usesCharacterRAM;

		std::vector<Byte> m_characterRAM;

	};
}
#endif // MAPPERNROM_H
