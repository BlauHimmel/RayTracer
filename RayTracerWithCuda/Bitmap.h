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

			uint16 Type;			//�ļ����ͣ�������0x424D�����ַ���BM��
			uint32 Size;			//�ļ���С
			uint16 Reserved1;		//������1
			uint16 Reserved2;		//������2
			uint32 OffBits;			//���ļ�ͷ��ʵ��λͼ���ݵ�ƫ���ֽ���

			uint32 HeaderSize() const;
			void Clear();

		};

		struct BitmapInformationHeader
		{

			uint32 Size;			//��Ϣͷ��С
			uint32 Width;			//ͼ����  
			uint32 Height;			//ͼ��߶�
			uint16 Planes;			//λƽ����������Ϊ1 
			uint16 BitCount;		//ÿ����λ�� 
			uint32 Compression;		//ѹ������ 
			uint32 SizeImage;		//ѹ��ͼ���С�ֽ��� 
			uint32 XPelsPerMeter;	//ˮƽ�ֱ���  
			uint32 YPelsPerMeter;	//��ֱ�ֱ��� 
			uint32 ClrUsed;			//λͼʵ���õ���ɫ����
			uint32 ClrImportant;	//��λͼ����Ҫ��ɫ���� 

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