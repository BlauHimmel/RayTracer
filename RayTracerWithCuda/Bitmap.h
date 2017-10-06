#pragma once

#include "ToolsDependency.h"

#include "ArrayList.hpp"
#include "Array.hpp"
#include "Color.h"

using namespace EasyContainer;

namespace EasyTools
{

	class Bitmap
	{

	private:

		String m_Filename;
		uint32 m_Width;
		uint32 m_Height;
		uint32 m_RowIncrement;
		uint32 m_BytesPerPixel;
		ArrayList<uint8> m_Data;

	public:

		Bitmap();
		Bitmap(uint32 Width, uint32 Height);
		Bitmap(const String& Filename);
		Bitmap(const Bitmap& Other);

	public:

		Bitmap& operator = (const Bitmap& Other);
		bool operator ! () const;

	public:

		bool IsValid() const;
		uint8 GetRedChannel(uint32 X, uint32 Y) const;
		uint8 GetGreenChannel(uint32 X, uint32 Y) const;
		uint8 GetBlueChannel(uint32 X, uint32 Y) const;
		void SetRedChannel(uint32 X, uint32 Y, uint8 Value);
		void SetGreenChannel(uint32 X, uint32 Y, uint8 Value);
		void SetBlueChannel(uint32 X, uint32 Y, uint8 Value);
		Array<uint8> GetRedChannel() const;
		Array<uint8> GetGreenChannel() const;
		Array<uint8> GetBlueChannel() const;
		void SetRedChannel(Array<uint8>& RedArray);
		void SetGreenChannel(Array<uint8>& GreenArray);
		void SetBlueChannel(Array<uint8>& BlueArray);
		void SetChannels(Array<uint8>& RedArray, Array<uint8>& GreenArray, Array<uint8>& BlueArray);
		Color GetPixel(uint8 X, uint8 Y) const;
		void SetPixel(uint8 X, uint8 Y, const Color& Color);
		uint32 Width() const;
		uint32 Height() const;
		uint32 BytesPerPixel() const;
		uint32 PixelCount() const;
		void Save(const String& Filename) const;
		bool CopyFrom(const Bitmap& Image);

	public:

		static uint32 FileSize(const String& Filename);

	private:

		void LoadBitmap();
		void CreateBitmap();

	private:

		struct BitmapFileHeader
		{

			uint16 Type;			//文件类型，必须是0x424D，即字符“BM”
			uint32 Size;			//文件大小
			uint16 Reserved1;		//保留字1
			uint16 Reserved2;		//保留字2
			uint32 OffBits;			//从文件头到实际位图数据的偏移字节数

			uint32 HeaderSize() const;
			void Clear();

		};

		struct BitmapInformationHeader
		{

			uint32 Size;			//信息头大小
			uint32 Width;			//图像宽度  
			uint32 Height;			//图像高度
			uint16 Planes;			//位平面数，必须为1 
			uint16 BitCount;		//每像素位数 
			uint32 Compression;		//压缩类型 
			uint32 SizeImage;		//压缩图像大小字节数 
			uint32 XPelsPerMeter;	//水平分辨率  
			uint32 YPelsPerMeter;	//垂直分辨率 
			uint32 ClrUsed;			//位图实际用到的色彩数
			uint32 ClrImportant;	//本位图中重要的色彩数 

			uint32 HeaderSize() const;
			void Clear();

		};

	private:

		void ReadBitmapFileHeader(std::ifstream& Stream, BitmapFileHeader& BitmapFileHeader);
		void WriteBitmapFileHeader(std::ofstream& Stream, const BitmapFileHeader& BitmapFileHeader) const;
		void ReadBitmapInformationHeader(std::ifstream& Stream, BitmapInformationHeader& BitmapInformationHeader);
		void WriteBitmapInformationHeader(std::ofstream& Stream, const BitmapInformationHeader& BitmapInformationHeader) const;
	
		uint8* Row(uint32 RowIndex);

	private:

		bool IsBigEndian() const;
		uint16 Flip(uint16 Value) const;
		uint32 Flip(uint32 Value) const;

	private:

		template <typename TValue>
		void Read(std::ifstream& Stream, TValue& Value) const;
		
		template <typename TValue>
		void Write(std::ofstream& Stream, const TValue& Value) const;

	};

	template<typename TValue>
	inline void Bitmap::Read(std::ifstream& Stream, TValue& Value) const
	{
		Stream.read(reinterpret_cast<int8*>(&Value), sizeof(TValue));
	}

	template<typename TValue>
	inline void Bitmap::Write(std::ofstream& Stream, const TValue & Value) const
	{
		Stream.write(reinterpret_cast<const int8*>(&Value), sizeof(TValue));
	}
}