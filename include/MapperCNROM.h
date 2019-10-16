#ifndef MAPPERCNROM_H
#define MAPPERCNROM_H

#include "Mapper.h"

namespace nes
{
	class MapperCNROM : public Mapper
	{
	public:
		explicit MapperCNROM(Cartridge &cart);

		void writePRG(Address addr, Byte value) override;

		Byte readPRG(Address addr) override;

		const Byte *getPagePtr(Address addr) override;

		Byte readCHR(Address addr) override;

		void writeCHR(Address addr, Byte value) override;

	private:
		bool m_oneBank;

		Address m_selectCHR;
	};
}
#endif // MAPPERCNROM_H
