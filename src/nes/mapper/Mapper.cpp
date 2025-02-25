#include "nes/mapper/Mapper.h"

#include <utility>
#include "nes/mapper/MapperNROM.h"
#include "nes/mapper/MapperSxROM.h"
#include "nes/mapper/MapperUxROM.h"
#include "nes/mapper/MapperCNROM.h"

namespace nes
{
	namespace mapper
	{
		NameTableMirroring Mapper::getNameTableMirroring()
		{
			return static_cast<NameTableMirroring>(m_cartridge.getNameTableMirroring());
		}

		std::unique_ptr<Mapper>
		Mapper::createMapper(Mapper::Type mapper_t, nes::Cartridge &cart, const std::function<void(void)> &mirroring_cb)
		{
			std::unique_ptr<Mapper> ret(nullptr);
			switch (mapper_t)
			{
				case NROM:
					ret.reset(new MapperNROM(cart));
					break;
				case SxROM:
					ret.reset(new MapperSxROM(cart, mirroring_cb));
					break;
				case UxROM:
					ret.reset(new MapperUxROM(cart));
					break;
				case CNROM:
					ret.reset(new MapperCNROM(cart));
					break;
				default:
					break;
			}
			return ret;
		}
	}
}