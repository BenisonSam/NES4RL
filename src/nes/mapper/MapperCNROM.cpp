#include "nes/mapper/MapperCNROM.h"
#include "utility/Log.h"

using namespace utility;

namespace nes
{
	namespace mapper
	{
		MapperCNROM::MapperCNROM(Cartridge &cart) :
				Mapper(cart, Mapper::CNROM),
				m_selectCHR(0)
		{
			m_oneBank = cart.getROM().size() == 0x4000;
		}

		Byte MapperCNROM::readPRG(Address addr)
		{
			if (!m_oneBank)
				return m_cartridge.getROM()[addr - 0x8000];
			else //mirrored
				return m_cartridge.getROM()[(addr - 0x8000) & 0x3fff];
		}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

		void MapperCNROM::writePRG(Address addr, Byte value)
		{
			m_selectCHR = static_cast<Address>(value & 0x3);
		}

#pragma clang diagnostic pop

		const Byte *MapperCNROM::getPagePtr(Address addr)
		{
			if (!m_oneBank)
				return &m_cartridge.getROM()[addr - 0x8000];
			else //mirrored
				return &m_cartridge.getROM()[(addr - 0x8000) & 0x3fff];
		}

		Byte MapperCNROM::readCHR(Address addr)
		{
			return m_cartridge.getVROM()[addr | (m_selectCHR << 13)];
		}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

		void MapperCNROM::writeCHR(Address addr, Byte value)
		{
			LOG(Info) << "Read-only CHR memory write attempt at " << std::hex << addr << std::endl;
		}

#pragma clang diagnostic pop
	}
}