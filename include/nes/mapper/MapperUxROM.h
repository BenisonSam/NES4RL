#ifndef MAPPERUXROM_H
#define MAPPERUXROM_H

#include "Mapper.h"

namespace nes
{
	namespace mapper
	{
		class MapperUxROM : public Mapper
		{
		public:
			explicit MapperUxROM(Cartridge &cart);

			void writePRG(Address addr, Byte value) override;

			Byte readPRG(Address addr) override;

			const Byte *getPagePtr(Address addr) override;

			Byte readCHR(Address addr) override;

			void writeCHR(Address addr, Byte value) override;

		private:
			bool m_usesCharacterRAM;

			const Byte *m_lastBankPtr;
			Address m_selectPRG;

			std::vector<Byte> m_characterRAM;

		};
	}
}
#endif // MAPPERUXROM_H
