#include "stdafx.h"

#include "Bitmap.h"


namespace EasyTools
{

	Bitmap::Bitmap() : 
		m_Filename(""), 
		m_ChannelMode(ChannelMode::BGR_MODE),
		m_Width(0), 
		m_Height(0), 
		m_RowIncrement(0), 
		m_BytesPerPixel(3)
	{

	}

	Bitmap::Bitmap(uint32 Width, uint32 Height) :
		m_Filename(""),
		m_ChannelMode(ChannelMode::BGR_MODE),
		m_Width(Width),
		m_Height(Height),
		m_RowIncrement(0),
		m_BytesPerPixel(3)
	{
		CreateBitmap();
	}

	Bitmap::Bitmap(const String& Filename) :
		m_Filename(Filename),
		m_ChannelMode(ChannelMode::BGR_MODE),
		m_Width(0),
		m_Height(0),
		m_RowIncrement(0),
		m_BytesPerPixel(3)
	{
		LoadBitmap();
	}

	Bitmap::Bitmap(const Bitmap& Other) :
		m_Filename(Other.m_Filename),
		m_ChannelMode(ChannelMode::BGR_MODE),
		m_Width(Other.m_Width),
		m_Height(Other.m_Height),
		m_RowIncrement(0),
		m_BytesPerPixel(3), 
		m_Data(Other.m_Data)
	{
		CreateBitmap();
	}

	bool Bitmap::IsValid() const
	{
		return 
			m_Data.Size() == 0 ||
			m_Width == 0 ||
			m_Height == 0 ||
			m_RowIncrement;
	}

	uint8 Bitmap::GetRedChannel(uint32 X, uint32 Y) const
	{
		return m_Data[static_cast<int32>(Y * m_RowIncrement + X * m_BytesPerPixel + 2)];
	}

	uint8 Bitmap::GetGreenChannel(uint32 X, uint32 Y) const
	{
		return m_Data[static_cast<int32>(Y * m_RowIncrement + X * m_BytesPerPixel + 1)];
	}

	uint8 Bitmap::GetBlueChannel(uint32 X, uint32 Y) const
	{
		return m_Data[static_cast<int32>(Y * m_RowIncrement + X * m_BytesPerPixel + 0)];
	}
	
	void Bitmap::SetRedChannel(uint32 X, uint32 Y, uint8 Value)
	{
		m_Data[static_cast<int32>(Y * m_RowIncrement + X * m_BytesPerPixel + 2)] = Value;
	}
	
	void Bitmap::SetGreenChannel(uint32 X, uint32 Y, uint8 Value)
	{
		m_Data[static_cast<int32>(Y * m_RowIncrement + X * m_BytesPerPixel + 1)] = Value;
	}
	
	void Bitmap::SetBlueChannel(uint32 X, uint32 Y, uint8 Value)
	{
		m_Data[static_cast<int32>(Y * m_RowIncrement + X * m_BytesPerPixel + 0)] = Value;
	}
	
	Color Bitmap::GetPixel(uint8 X, uint8 Y) const
	{
		uint32 YOffset = Y * m_RowIncrement;
		uint32 XOffset = X * m_BytesPerPixel;
		uint8 B = m_Data[YOffset + XOffset + 0];
		uint8 G = m_Data[YOffset + XOffset + 1];
		uint8 R = m_Data[YOffset + XOffset + 2];
		return Color(R, G, B);
	}
	
	void Bitmap::SetPixel(uint8 X, uint8 Y, const Color& Color)
	{
		uint32 YOffset = Y * m_RowIncrement;
		uint32 XOffset = X * m_BytesPerPixel;
		m_Data[YOffset + XOffset + 0] = Color.B();
		m_Data[YOffset + XOffset + 1] = Color.G();
		m_Data[YOffset + XOffset + 2] = Color.R();
	}
	
	uint32 Bitmap::Width() const
	{
		return m_Width;
	}
	
	uint32 Bitmap::Height() const
	{
		return m_Height;
	}
	
	uint32 Bitmap::BytesPerPixel() const
	{
		return m_BytesPerPixel;
	}
	
	uint32 Bitmap::PixelCount() const
	{
		return m_Width * m_Height;
	}
	
	void Bitmap::Save(const String& Filename) const
	{
		std::ofstream Stream(Filename.c_str(), std::ios::binary);

		if (!Stream)
		{
			DEBUG_ERROR("Could Not Open File For Writing");
		}

		BitmapInformationHeader InformationHeader;
		InformationHeader.Width = m_Width;
		InformationHeader.Height = m_Height;
		InformationHeader.BitCount = static_cast<uint16>(m_BytesPerPixel << 3);
		InformationHeader.ClrImportant = 0;
		InformationHeader.ClrUsed = 0;
		InformationHeader.Compression = 0;
		InformationHeader.Planes = 1;
		InformationHeader.Size = InformationHeader.HeaderSize();
		InformationHeader.XPelsPerMeter = 0;
		InformationHeader.YPelsPerMeter = 0;
		InformationHeader.SizeImage = (((m_Width * m_BytesPerPixel) + 3) & 0x0000FFFC) * m_Height;

		BitmapFileHeader FileHeader;
		FileHeader.Type = 19778;
		FileHeader.Size = InformationHeader.HeaderSize() + FileHeader.HeaderSize() + InformationHeader.SizeImage;
		FileHeader.Reserved1 = 0;
		FileHeader.Reserved2 = 0;
		FileHeader.OffBits = InformationHeader.HeaderSize() + FileHeader.HeaderSize();

		WriteBitmapFileHeader(Stream, FileHeader);
		WriteBitmapInformationHeader(Stream, InformationHeader);

		uint32 PaddingSize = (4 - ((3 * m_Width) % 4)) % 4;
		int8 PaddingData[4] = { 0, 0, 0, 0 };

		for (uint32 i = 0; i < m_Height; ++i)
		{
			const uint8* DataPtr = &m_Data[(m_RowIncrement * (m_Height - i - 1))];

			Stream.write(reinterpret_cast<const char*>(DataPtr), sizeof(unsigned char) * m_BytesPerPixel * m_Width);
			Stream.write(PaddingData, PaddingSize);
		}

		Stream.close();
	}

	bool Bitmap::CopyFrom(const Bitmap& Image)
	{
		if (Image.m_Height != m_Height || Image.m_Width != m_Width)
		{
			return false;
		}

		m_Data = Image.m_Data;
		return true;
	}

	uint32 Bitmap::FileSize(const String& Filename)
	{
		std::ifstream File(Filename.c_str(), std::ios::in | std::ios::binary);
		if (!File)
		{
			DEBUG_ERROR("File Not Found");
		}
		File.seekg(0, std::ios::end);
		return static_cast<uint32>(File.tellg());
	}

	void Bitmap::LoadBitmap()
	{
		std::ifstream Stream(m_Filename, std::ios::binary);

		if (!Stream)
		{
			DEBUG_ERROR("File Not Found");
		}

		m_Width = 0;
		m_Height = 0;

		BitmapFileHeader FileHeader;
		BitmapInformationHeader InformationHeader;

		FileHeader.Clear();
		InformationHeader.Clear();

		ReadBitmapFileHeader(Stream, FileHeader);
		ReadBitmapInformationHeader(Stream, InformationHeader);
		
		if (FileHeader.Type != 19778)
		{
			FileHeader.Clear();
			InformationHeader.Clear();

			Stream.close();

			DEBUG_ERROR("Invalid Type Value, Expected 19778");
		}

		if (InformationHeader.BitCount != 24)
		{
			FileHeader.Clear();
			InformationHeader.Clear();

			Stream.close();

			DEBUG_ERROR("Invalid Bit Depth, Expected 24");
		}

		if (InformationHeader.Size != InformationHeader.HeaderSize())
		{
			FileHeader.Clear();
			InformationHeader.Clear();

			Stream.close();

			DEBUG_ERROR("Invalid InformationHeader Size");
		}

		m_Width = InformationHeader.Width;
		m_Height = InformationHeader.Height;

		m_BytesPerPixel = InformationHeader.BitCount >> 3;

		uint32 PaddingSize = (4 - ((3 * m_Width) % 4)) % 4;
		int8 PaddingData[4] = { 0, 0, 0, 0 };

		uint32 BitmapFileSize = FileSize(m_Filename);
		uint32 BitmapLogicalSize = (m_Height * m_Width * m_BytesPerPixel) + m_Height * PaddingSize + InformationHeader.HeaderSize() + FileHeader.HeaderSize();

		if (BitmapFileSize != BitmapLogicalSize)
		{
			FileHeader.Clear();
			InformationHeader.Clear();

			Stream.close();

			DEBUG_ERROR("Mismatch Between Logical and Actual File Size Of Bitmap");
		}

		CreateBitmap();

		for (uint32 i = 0; i < m_Height; i++)
		{
			uint8* DataPtr = Row(m_Height - i - 1);

			Stream.read(reinterpret_cast<int8*>(DataPtr), m_BytesPerPixel * m_Width * sizeof(int8));
			Stream.read(PaddingData, PaddingSize);
		}
	}

	void Bitmap::CreateBitmap()
	{
		m_RowIncrement = m_Width * m_BytesPerPixel;
		m_Data.Resize(m_Height * m_RowIncrement);
	}

	uint32 Bitmap::BitmapFileHeader::HeaderSize() const
	{
		return
			sizeof(Type) +
			sizeof(Size) +
			sizeof(Reserved1) +
			sizeof(Reserved2) +
			sizeof(OffBits);
	}

	void Bitmap::BitmapFileHeader::Clear()
	{
		std::memset(this, 0, sizeof(BitmapFileHeader));
	}

	uint32 Bitmap::BitmapInformationHeader::HeaderSize() const
	{
		return
			sizeof(Size) +
			sizeof(Width) +
			sizeof(Height) +
			sizeof(Planes) +
			sizeof(BitCount) +
			sizeof(Compression) +
			sizeof(SizeImage) +
			sizeof(XPelsPerMeter) +
			sizeof(YPelsPerMeter) +
			sizeof(ClrUsed) +
			sizeof(ClrImportant);
	}

	void Bitmap::BitmapInformationHeader::Clear()
	{
		std::memset(this, 0, sizeof(BitmapInformationHeader));
	}

	void Bitmap::ReadBitmapFileHeader(std::ifstream& Stream, BitmapFileHeader& BitmapFileHeader)
	{
		Read(Stream, BitmapFileHeader.Type);
		Read(Stream, BitmapFileHeader.Size);
		Read(Stream, BitmapFileHeader.Reserved1);
		Read(Stream, BitmapFileHeader.Reserved2);
		Read(Stream, BitmapFileHeader.OffBits);

		if (IsBigEndian())
		{
			BitmapFileHeader.Type = Flip(BitmapFileHeader.Type);
			BitmapFileHeader.Size = Flip(BitmapFileHeader.Size);
			BitmapFileHeader.Reserved1 = Flip(BitmapFileHeader.Reserved1);
			BitmapFileHeader.Reserved2 = Flip(BitmapFileHeader.Reserved2);
			BitmapFileHeader.OffBits = Flip(BitmapFileHeader.OffBits);
		}
	}

	void Bitmap::WriteBitmapFileHeader(std::ofstream& Stream, const BitmapFileHeader& BitmapFileHeader) const
	{
		if (IsBigEndian())
		{
			Write(Stream, Flip(BitmapFileHeader.Type));
			Write(Stream, Flip(BitmapFileHeader.Size));
			Write(Stream, Flip(BitmapFileHeader.Reserved1));
			Write(Stream, Flip(BitmapFileHeader.Reserved2));
			Write(Stream, Flip(BitmapFileHeader.OffBits));
		}
		else
		{
			Write(Stream, BitmapFileHeader.Type);
			Write(Stream, BitmapFileHeader.Size);
			Write(Stream, BitmapFileHeader.Reserved1);
			Write(Stream, BitmapFileHeader.Reserved2);
			Write(Stream, BitmapFileHeader.OffBits);
		}
	}

	void Bitmap::ReadBitmapInformationHeader(std::ifstream& Stream, BitmapInformationHeader& BitmapInformationHeader)
	{
		Read(Stream, BitmapInformationHeader.Size);
		Read(Stream, BitmapInformationHeader.Width);
		Read(Stream, BitmapInformationHeader.Height);
		Read(Stream, BitmapInformationHeader.Planes);
		Read(Stream, BitmapInformationHeader.BitCount);
		Read(Stream, BitmapInformationHeader.Compression);
		Read(Stream, BitmapInformationHeader.SizeImage);
		Read(Stream, BitmapInformationHeader.XPelsPerMeter);
		Read(Stream, BitmapInformationHeader.YPelsPerMeter);
		Read(Stream, BitmapInformationHeader.ClrUsed);
		Read(Stream, BitmapInformationHeader.ClrImportant);

		if (IsBigEndian())
		{
			BitmapInformationHeader.Size = Flip(BitmapInformationHeader.Size);
			BitmapInformationHeader.Width = Flip(BitmapInformationHeader.Width);
			BitmapInformationHeader.Height = Flip(BitmapInformationHeader.Height);
			BitmapInformationHeader.Planes = Flip(BitmapInformationHeader.Planes);
			BitmapInformationHeader.BitCount = Flip(BitmapInformationHeader.BitCount);
			BitmapInformationHeader.Compression = Flip(BitmapInformationHeader.Compression);
			BitmapInformationHeader.SizeImage = Flip(BitmapInformationHeader.SizeImage);
			BitmapInformationHeader.XPelsPerMeter = Flip(BitmapInformationHeader.XPelsPerMeter);
			BitmapInformationHeader.YPelsPerMeter = Flip(BitmapInformationHeader.YPelsPerMeter);
			BitmapInformationHeader.ClrUsed = Flip(BitmapInformationHeader.ClrUsed);
			BitmapInformationHeader.ClrImportant = Flip(BitmapInformationHeader.ClrImportant);
		}
	}

	void Bitmap::WriteBitmapInformationHeader(std::ofstream& Stream, const BitmapInformationHeader& BitmapInformationHeader) const
	{
		if (IsBigEndian())
		{
			Write(Stream, Flip(BitmapInformationHeader.Size));
			Write(Stream, Flip(BitmapInformationHeader.Width));
			Write(Stream, Flip(BitmapInformationHeader.Height));
			Write(Stream, Flip(BitmapInformationHeader.Planes));
			Write(Stream, Flip(BitmapInformationHeader.BitCount));
			Write(Stream, Flip(BitmapInformationHeader.Compression));
			Write(Stream, Flip(BitmapInformationHeader.SizeImage));
			Write(Stream, Flip(BitmapInformationHeader.XPelsPerMeter));
			Write(Stream, Flip(BitmapInformationHeader.YPelsPerMeter));
			Write(Stream, Flip(BitmapInformationHeader.ClrUsed));
			Write(Stream, Flip(BitmapInformationHeader.ClrImportant));
		}
		else
		{
			Write(Stream, BitmapInformationHeader.Size);
			Write(Stream, BitmapInformationHeader.Width);
			Write(Stream, BitmapInformationHeader.Height);
			Write(Stream, BitmapInformationHeader.Planes);
			Write(Stream, BitmapInformationHeader.BitCount);
			Write(Stream, BitmapInformationHeader.Compression);
			Write(Stream, BitmapInformationHeader.SizeImage);
			Write(Stream, BitmapInformationHeader.XPelsPerMeter);
			Write(Stream, BitmapInformationHeader.YPelsPerMeter);
			Write(Stream, BitmapInformationHeader.ClrUsed);
			Write(Stream, BitmapInformationHeader.ClrImportant);
		}
	}

	uint8* Bitmap::Row(uint32 RowIndex)
	{
		return const_cast<uint8*>(&m_Data[static_cast<int32>(RowIndex * m_RowIncrement)]);
	}

	bool Bitmap::IsBigEndian() const
	{
		uint32 Value = 0x01;
		return 1 != reinterpret_cast<int8*>(&Value)[0];
	}

	uint16 Bitmap::Flip(uint16 Value) const
	{
		return (Value >> 8) | (Value << 8);
	}

	uint32 Bitmap::Flip(uint32 Value) const
	{
		return 
			((Value & 0xff000000) >> 0x18) |
			((Value & 0x000000ff) << 0x18) |
			((Value & 0x00ff0000) >> 0x08) |
			((Value & 0x0000ff00) << 0x08);
	}
}
