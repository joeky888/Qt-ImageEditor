#include "Application.h"
#include "qt_opengl_framework.h"
#include <vector>

Application::Application()
{

}
Application::~Application()
{

}
//****************************************************************************
//
// * 初始畫面，並顯示Ntust.png圖檔
// 
//============================================================================
void Application::createScene( void )
{
	
	ui_instance = Qt_Opengl_Framework::getInstance();
	
}

//****************************************************************************
//
// * 打開指定圖檔
// 
//============================================================================
void Application::openImage( QString filePath )
{
	mImageSrc.load(filePath);
	mImageDst.load(filePath);

	renew();

	img_data = mImageSrc.bits();
	img_width = mImageSrc.width();
	img_height = mImageSrc.height();

	ui_instance->ui.label->setFixedHeight(img_height);
	ui_instance->ui.label->setFixedWidth(img_width);


}
//****************************************************************************
//
// * 刷新畫面
// 
//============================================================================
void Application::renew()
{
	ui_instance = Qt_Opengl_Framework::getInstance();

	ui_instance->ui.label->clear();
	ui_instance->ui.label->setPixmap(QPixmap::fromImage(mImageDst));

    ui_instance->ui.label->setFixedHeight(mImageDst.height());
    ui_instance->ui.label->setFixedWidth(mImageDst.width());
}

//****************************************************************************
//
// * 畫面初始化
// 
//============================================================================
void Application::reload()
{
	ui_instance = Qt_Opengl_Framework::getInstance();

	ui_instance->ui.label->clear();
	ui_instance->ui.label->setPixmap(QPixmap::fromImage(mImageSrc));
}

//****************************************************************************
//
// * 儲存圖檔
// 
//============================================================================
void Application::saveImage(QString filePath )
{
	mImageDst.save(filePath);
}

//****************************************************************************
//
// * 將圖檔資料轉換為RGB色彩資料
// 
//============================================================================
unsigned char* Application::To_RGB( void )
{
	unsigned char *rgb = new unsigned char[img_width * img_height * 3];
	int i, j;

	if (! img_data )
		return NULL;

	// Divide out the alpha
	for (i = 0; i < img_height; i++)
	{
		int in_offset = i * img_width * 4;
		int out_offset = i * img_width * 3;

		for (j = 0 ; j < img_width ; j++)
		{
			RGBA_To_RGB(img_data + (in_offset + j*4), rgb + (out_offset + j*3));
		}
	}

	return rgb;
}

void Application::RGBA_To_RGB( unsigned char *rgba, unsigned char *rgb )
{
	const unsigned char	BACKGROUND[3] = { 0, 0, 0 };

	unsigned char  alpha = rgba[3];

	if (alpha == 0)
	{
		rgb[0] = BACKGROUND[0];
		rgb[1] = BACKGROUND[1];
		rgb[2] = BACKGROUND[2];
	}
	else
	{
		float	alpha_scale = (float)255 / (float)alpha;
		int	val;
		int	i;

		for (i = 0 ; i < 3 ; i++)
		{
			val = (int)floor(rgba[i] * alpha_scale);
			if (val < 0)
				rgb[i] = 0;
			else if (val > 255)
				rgb[i] = 255;
			else
				rgb[i] = val;
		}
	}
}
//------------------------Color------------------------

///////////////////////////////////////////////////////////////////////////////
//
//  Convert image to grayscale.  Red, green, and blue channels should all 
//  contain grayscale value.  Alpha channel shoould be left unchanged.  Return
//  success of operation.
//
///////////////////////////////////////////////////////////////////////////////
void Application::Gray()
{
	unsigned char *rgb = To_RGB();

	for (int i=0; i<img_height; i++)
	{
		for (int j=0; j<img_width; j++)
		{
			int offset_rgb = i*img_width*3+j*3;
			int offset_rgba = i*img_width*4+j*4;
            unsigned char gray = 0.3 * rgb[offset_rgb + rr] + 0.59 * rgb[offset_rgb + gg] + 0.11 * rgb[offset_rgb + bb];

			for (int k=0; k<3; k++)
                img_data[offset_rgba+k] = gray;
			img_data[offset_rgba + aa] = WHITE;
		}
	}
	
	delete[] rgb;
	mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
	renew();
}
///////////////////////////////////////////////////////////////////////////////
//
//  Convert the image to an 8 bit image using uniform quantization.  Return 
//  success of operation.
//
///////////////////////////////////////////////////////////////////////////////
void Application::Quant_Uniform()
{
	unsigned char *rgb = this->To_RGB();

    for (int i=0; i<img_height; i++)
    {
        for (int j=0; j<img_width; j++)
        {
            int offset_rgb = i*img_width*3+j*3;
            int offset_rgba = i*img_width*4+j*4;

            img_data[offset_rgba + rr] = (rgb[offset_rgb + rr] >> 5) << 5;
            img_data[offset_rgba + gg] = (rgb[offset_rgb + gg] >> 5) << 5;
            img_data[offset_rgba + bb] = (rgb[offset_rgb + bb] >> 6) << 6;
//            img_data[offset_rgba + aa] = WHITE;
        }
    }

	delete[] rgb;
	mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
	renew();
}
///////////////////////////////////////////////////////////////////////////////
//
//  Convert the image to an 8 bit image using populosity quantization.  
//  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////

inline int findColorInQVector(QVector<QVector3D> vec, QVector3D val)
{
    for(int i = 0; i < vec.size(); i++)
        if(vec[i] == val)
            return i;// found
    return -1;// not found
}

void sortColorTable(QVector<QVector3D>& ColorTable, QVector<int>& ColorTableCount)
{
    for(int i = 0; i < 256; i++)
    {
        int Max = i;
        for(int j = i + 1; j < ColorTableCount.size(); j++){
            if(ColorTableCount[j] > ColorTableCount[Max]){
                Max = j;
            }
        }

        if(Max != i){
            int temp = ColorTableCount[Max];
            ColorTableCount[Max] = ColorTableCount[i];
            ColorTableCount[i] = temp;

            QVector3D temp2 = ColorTable[Max];
            ColorTable[Max] = ColorTable[i];
            ColorTable[i] = temp2;
        }
    }
}

inline int ClosestColor(QVector<QVector3D>& ColorTable, QVector3D CurrentImgData)
{
    float minDistance = 500000, currentDistance;
    int minIndex = 0;
    for(int i = 0; i < 256; i++){
        currentDistance = (ColorTable[i].x()-CurrentImgData.x()) * (ColorTable[i].x()-CurrentImgData.x())
                        + (ColorTable[i].y()-CurrentImgData.y()) * (ColorTable[i].y()-CurrentImgData.y())
                        + (ColorTable[i].z()-CurrentImgData.z()) * (ColorTable[i].z()-CurrentImgData.z());
        if(minDistance > currentDistance){
            minDistance = currentDistance;
            minIndex = i;
        }
    }
    return minIndex;
}

void Application::Quant_Populosity()
{
	unsigned char *rgb = this->To_RGB();
    QVector<QVector3D> ColorTable;// rank for constructing 256 colors table
    QVector<int>       ColorTableCount;

    for (int i=0; i<img_height; i++)
    {
        for (int j=0; j<img_width; j++)
        {
            int offset_rgb = i*img_width*3+j*3;
            int offset_rgba = i*img_width*4+j*4;

            img_data[offset_rgba + rr] = (rgb[offset_rgb + rr] >> 3) << 3;
            img_data[offset_rgba + gg] = (rgb[offset_rgb + gg] >> 3) << 3;
            img_data[offset_rgba + bb] = (rgb[offset_rgb + bb] >> 3) << 3;

            /* check if this color is already in the table, if not, push it in. */
            int index = findColorInQVector(ColorTable, QVector3D(img_data[offset_rgba + rr], img_data[offset_rgba + gg], img_data[offset_rgba + bb]));
            if(index == -1){
                ColorTable.push_back(QVector3D(img_data[offset_rgba + rr], img_data[offset_rgba + gg], img_data[offset_rgba + bb]));
                ColorTableCount.push_back(1);
            }else{
                ColorTableCount[index]++;
            }
        }
    }

    /* sort the color table */
    sortColorTable(ColorTable, ColorTableCount);

    /* find the closest color in the color table and replace it */
    for (int i=0; i<img_height; i++)
    {
        for (int j=0; j<img_width; j++)
        {
            int offset_rgba = i*img_width*4+j*4;

            int ClosestColorIndex = ClosestColor(ColorTable,QVector3D(img_data[offset_rgba + rr], img_data[offset_rgba + gg], img_data[offset_rgba + bb]));
            img_data[offset_rgba + rr] = ColorTable[ClosestColorIndex].x();
            img_data[offset_rgba + gg] = ColorTable[ClosestColorIndex].y();
            img_data[offset_rgba + bb] = ColorTable[ClosestColorIndex].z();
        }
    }
	delete[] rgb;
	mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
	renew();
}

//------------------------Dithering------------------------

///////////////////////////////////////////////////////////////////////////////
//
//  Dither the image using a threshold of 1/2.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
void Application::Dither_Threshold()
{
	unsigned char *rgb = this->To_RGB();

    for (int i=0; i<img_height; i++)
    {
        for (int j=0; j<img_width; j++)
        {
            int offset_rgb = i*img_width*3+j*3;
            int offset_rgba = i*img_width*4+j*4;

            unsigned char gray = 0.3 * rgb[offset_rgb + rr] + 0.59 * rgb[offset_rgb + gg] + 0.11 * rgb[offset_rgb + bb];

            img_data[offset_rgba + rr] = img_data[offset_rgba + gg] = img_data[offset_rgba + bb] = gray > 127 ? WHITE : BLACK;
        }
    }

	delete[] rgb;
	mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
	renew();
}
///////////////////////////////////////////////////////////////////////////////
//
//  Dither image using random dithering.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
float randomNumber(int min, int max){
    return qrand() % ((max + 1) - min) + min;
}

void Application::Dither_Random()
{
	unsigned char *rgb = this->To_RGB();
    float averageGray = 0;
    QVector<float> grayTable;
    /* compute total brightness */
    for (int i=0; i<img_height; i++)
    {
        for (int j=0; j<img_width; j++)
        {
            int offset_rgb = i*img_width*3+j*3;
            float gray = float(0.3 * rgb[offset_rgb + rr] + 0.59 * rgb[offset_rgb + gg] + 0.11 * rgb[offset_rgb + bb]);
            grayTable.push_back(gray);
            averageGray += gray;
        }
    }
    /* average brightness normalize */
    averageGray /= float(img_height * img_width * 256);
    /* sort grayTable */
    qSort(grayTable);
    /* costruct threshold */
    float threshold = grayTable[int(grayTable.size() * (1 - averageGray))];
    /* random value for threshold */
    int randMax = 0.2 * 256, randMin = -0.2 * 256;

    for (int i=0; i<img_height; i++)
    {
        for (int j=0; j<img_width; j++)
        {
            int offset_rgb = i*img_width*3+j*3;
            int offset_rgba = i*img_width*4+j*4;

            float gray = float(0.3 * rgb[offset_rgb + rr] + 0.59 * rgb[offset_rgb + gg] + 0.11 * rgb[offset_rgb + bb]);
            /* random threshold*/
            img_data[offset_rgba + rr] = img_data[offset_rgba + gg] = img_data[offset_rgba + bb] = gray > qBound(0, int(threshold + randomNumber(randMin, randMax)), 255) ? WHITE : BLACK;
        }
    }


	delete[] rgb;
	mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
	renew();
}
///////////////////////////////////////////////////////////////////////////////
//
//  Perform Floyd-Steinberg dithering on the image.  Return success of 
//  operation.
//
///////////////////////////////////////////////////////////////////////////////
int find_closest_palette_color(float oldpixel){
    return oldpixel > 127 ? 255 : 0;
}

void Application::Dither_FS()
{
	unsigned char *rgb = this->To_RGB();

    for (int i=0; i<img_height; i++)
    {
        for (int j=0; j<img_width; j++)
        {
            int offset_rgb = i*img_width*3+j*3;
            int offset_rgba = i*img_width*4+j*4;
            float gray = 0.3 * rgb[offset_rgb + rr] + 0.59 * rgb[offset_rgb + gg] + 0.11 * rgb[offset_rgb + bb];
            img_data[offset_rgba + rr] = img_data[offset_rgba + gg] = img_data[offset_rgba + bb] = gray;

        }
    }

    for (int i=0; i<img_height; i++)
    {
        if(i % 2 == 0){
            for (int j=0; j<img_width; j++){
                int offset_rgba = i*img_width*4+j*4;

                /* Floyd–Steinberg dithering algorithm "http://en.wikipedia.org/wiki/Floyd–Steinberg_dithering" */
                float oldpixel = qBound(0.0f, float(img_data[offset_rgba + rr]), 255.0f);
                float newpixel = find_closest_palette_color(oldpixel);
                float quant_error = oldpixel - newpixel;

                img_data[offset_rgba + rr] = img_data[offset_rgba + gg] = img_data[offset_rgba + bb] = newpixel;

                if(j+1 < img_width)
                    img_data[( i )*img_width*4+(j+1)*4 + rr] = img_data[( i )*img_width*4+(j+1)*4 + gg] = img_data[( i )*img_width*4+(j+1)*4 + bb] = img_data[( i )*img_width*4+(j+1)*4 + bb] + quant_error * (7/16.0);
                if(i+1 < img_height && j-1 >= 0)
                    img_data[(i+1)*img_width*4+(j-1)*4 + rr] = img_data[(i+1)*img_width*4+(j-1)*4 + gg] = img_data[(i+1)*img_width*4+(j-1)*4 + bb] = img_data[(i+1)*img_width*4+(j-1)*4 + bb] + quant_error * (3/16.0);
                if(i+1 < img_height)
                    img_data[(i+1)*img_width*4+( j )*4 + rr] = img_data[(i+1)*img_width*4+( j )*4 + gg] = img_data[(i+1)*img_width*4+( j )*4 + bb] = img_data[(i+1)*img_width*4+( j )*4 + bb] + quant_error * (5/16.0);
                if(i+1 < img_height && j+1 < img_width)
                    img_data[(i+1)*img_width*4+(j+1)*4 + rr] = img_data[(i+1)*img_width*4+(j+1)*4 + gg] = img_data[(i+1)*img_width*4+(j+1)*4 + bb] = img_data[(i+1)*img_width*4+(j+1)*4 + bb] + quant_error * (1/16.0);
            }
        }else{
            for (int j=img_width - 1; j>=0; j--){
                int offset_rgba = i*img_width*4+j*4;

                /* Floyd–Steinberg dithering algorithm "http://en.wikipedia.org/wiki/Floyd–Steinberg_dithering" */
                float oldpixel = qBound(0.0f, float(img_data[offset_rgba + rr]), 255.0f);
                float newpixel = find_closest_palette_color(oldpixel);
                float quant_error = oldpixel - newpixel;

                img_data[offset_rgba + rr] = img_data[offset_rgba + gg] = img_data[offset_rgba + bb] = newpixel;

                if(j-1 >= 0)
                    img_data[( i )*img_width*4+(j-1)*4 + rr] = img_data[( i )*img_width*4+(j-1)*4 + gg] = img_data[( i )*img_width*4+(j-1)*4 + bb] = img_data[( i )*img_width*4+(j-1)*4 + bb] + quant_error * (7/16.0);
                if(i+1 < img_height && j+1 < img_width)
                    img_data[(i+1)*img_width*4+(j+1)*4 + rr] = img_data[(i+1)*img_width*4+(j+1)*4 + gg] = img_data[(i+1)*img_width*4+(j+1)*4 + bb] = img_data[(i+1)*img_width*4+(j+1)*4 + bb] + quant_error * (3/16.0);
                if(i+1 < img_height)
                    img_data[(i+1)*img_width*4+( j )*4 + rr] = img_data[(i+1)*img_width*4+( j )*4 + gg] = img_data[(i+1)*img_width*4+( j )*4 + bb] = img_data[(i+1)*img_width*4+( j )*4 + bb] + quant_error * (5/16.0);
                if(i+1 < img_height && j-1 >= 0)
                    img_data[(i+1)*img_width*4+(j-1)*4 + rr] = img_data[(i+1)*img_width*4+(j-1)*4 + gg] = img_data[(i+1)*img_width*4+(j-1)*4 + bb] = img_data[(i+1)*img_width*4+(j-1)*4 + bb] + quant_error * (1/16.0);
            }
        }
    }

	delete[] rgb;
	mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
	renew();
}
///////////////////////////////////////////////////////////////////////////////
//
//  Dither the image while conserving the average brightness.  Return 
//  success of operation.
//
///////////////////////////////////////////////////////////////////////////////

void Application::Dither_Bright()
{
    unsigned char *rgb = this->To_RGB();
    float averageGray = 0;
    QVector<float> grayTable;
    /* compute total brightness */
    for (int i=0; i<img_height; i++)
    {
        for (int j=0; j<img_width; j++)
        {
            int offset_rgb = i*img_width*3+j*3;
            float gray = float(0.3 * rgb[offset_rgb + rr] + 0.59 * rgb[offset_rgb + gg] + 0.11 * rgb[offset_rgb + bb]);
            grayTable.push_back(gray);
            averageGray += gray;
        }
    }
    /* average brightness normalize */
    averageGray /= float(img_height * img_width * 256);
    /* sort grayTable */
    qSort(grayTable);
    /* costruct threshold */
    float threshold = grayTable[int(grayTable.size() * (1 - averageGray))];

    for (int i=0; i<img_height; i++)
    {
        for (int j=0; j<img_width; j++)
        {
            int offset_rgb = i*img_width*3+j*3;
            int offset_rgba = i*img_width*4+j*4;

            float gray = float(0.3 * rgb[offset_rgb + rr] + 0.59 * rgb[offset_rgb + gg] + 0.11 * rgb[offset_rgb + bb]);
            img_data[offset_rgba + rr] = img_data[offset_rgba + gg] = img_data[offset_rgba + bb] = gray > threshold ? WHITE : BLACK;
        }
    }

	delete[] rgb;
	mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
	renew();
}
///////////////////////////////////////////////////////////////////////////////
//
//  Perform clustered differing of the image.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
void Application::Dither_Cluster()
{
	unsigned char *rgb = this->To_RGB();
    double thresholdMatrix[4][4] = {
        0.7059, 0.3529, 0.5882, 0.2353,
        0.0588, 0.9412, 0.8235, 0.4118,
        0.4706, 0.7647, 0.8824, 0.1176,
        0.1765, 0.5294, 0.2941, 0.6471
    };
    for (int i=0; i<img_height; i++)
    {
        for (int j=0; j<img_width; j++)
        {
            int offset_rgb = i*img_width*3+j*3;
            int offset_rgba = i*img_width*4+j*4;

            float gray = float(0.3 * rgb[offset_rgb + rr] + 0.59 * rgb[offset_rgb + gg] + 0.11 * rgb[offset_rgb + bb]);

            img_data[offset_rgba + rr] = img_data[offset_rgba + gg] = img_data[offset_rgba + bb] = gray > thresholdMatrix[i % 4][j % 4] * 256.0 ? WHITE : BLACK;
        }
    }

	delete[] rgb;
	mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
	renew();
}
///////////////////////////////////////////////////////////////////////////////
//
//  Convert the image to an 8 bit image using Floyd-Steinberg dithering over
//  a uniform quantization - the same quantization as in Quant_Uniform.
//  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
inline int find_closest_palette_color(QVector<QVector3D> table, QVector3D oldpixal){
    float minDistance = 500000, currentDistance;
    int minIndex = 0;
    for(int i = 0; i < 256; i++){
        currentDistance = (table[i].x()-oldpixal.x()) * (table[i].x()-oldpixal.x())
                        + (table[i].y()-oldpixal.y()) * (table[i].y()-oldpixal.y())
                        + (table[i].z()-oldpixal.z()) * (table[i].z()-oldpixal.z());
        if(minDistance > currentDistance){
            minDistance = currentDistance;
            minIndex = i;
        }
    }
    return minIndex;
}

void Application::Dither_Color()
{
    unsigned char *rgb = this->To_RGB();
    float *img_dataTemp = new float[img_width * img_height *32];

    /* construct 256 color table */
    QVector<QVector3D> table;
    float red[]   = {0, 36, 73, 109, 146, 182, 219, 255};
    float green[] = {0, 36, 73, 109, 146, 182, 219, 255};
    float blue[]  = {0, 85, 170, 255};
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            for(int k = 0; k < 4; k++)
                table.push_back(QVector3D(red[i], green[j], blue[k]));

    /* store img_data to img_dataTemp, because unsigned char may cause overflow */
    for (int i=0; i<img_height; i++)
    {
        for (int j=0; j<img_width; j++)
        {
            int offset_rgba = i*img_width*4+j*4;

            img_dataTemp[offset_rgba + rr] = img_data[offset_rgba + rr];
            img_dataTemp[offset_rgba + gg] = img_data[offset_rgba + gg];
            img_dataTemp[offset_rgba + bb] = img_data[offset_rgba + bb];
        }
    }


    for (int i=0; i<img_height; i++)
    {
        if(i % 2 == 0){
            for (int j=0; j<img_width; j++){
                int offset_rgba = i*img_width*4+j*4;

                /* Floyd–Steinberg dithering algorithm "http://en.wikipedia.org/wiki/Floyd–Steinberg_dithering" */
                QVector3D oldpixel = QVector3D(qBound(0.0f, float(img_dataTemp[offset_rgba + rr]), 255.0f), qBound(0.0f, float(img_dataTemp[offset_rgba + gg]), 255.0f), qBound(0.0f, float(img_dataTemp[offset_rgba + bb]), 255.0f));
                QVector3D newpixel = table[find_closest_palette_color(table, oldpixel)];
                QVector3D quant_error = oldpixel - newpixel;

                img_dataTemp[offset_rgba + rr] = newpixel.x();
                img_dataTemp[offset_rgba + gg] = newpixel.y();
                img_dataTemp[offset_rgba + bb] = newpixel.z();

                if(j+1 < img_width){
                    img_dataTemp[( i )*img_width*4+(j+1)*4 + rr] += quant_error.x() * (7/16.0);
                    img_dataTemp[( i )*img_width*4+(j+1)*4 + gg] += quant_error.y() * (7/16.0);
                    img_dataTemp[( i )*img_width*4+(j+1)*4 + bb] += quant_error.z() * (7/16.0);
                }
                if(i+1 < img_height && j-1 >= 0){
                    img_dataTemp[(i+1)*img_width*4+(j-1)*4 + rr] += quant_error.x() * (3/16.0);
                    img_dataTemp[(i+1)*img_width*4+(j-1)*4 + gg] += quant_error.y() * (3/16.0);
                    img_dataTemp[(i+1)*img_width*4+(j-1)*4 + bb] += quant_error.z() * (3/16.0);
                }
                if(i+1 < img_height){
                    img_dataTemp[(i+1)*img_width*4+( j )*4 + rr] += quant_error.x() * (5/16.0);
                    img_dataTemp[(i+1)*img_width*4+( j )*4 + gg] += quant_error.y() * (5/16.0);
                    img_dataTemp[(i+1)*img_width*4+( j )*4 + bb] += quant_error.z() * (5/16.0);
                }
                if(i+1 < img_height && j+1 < img_width){
                    img_dataTemp[(i+1)*img_width*4+(j+1)*4 + rr] += quant_error.x() * (1/16.0);
                    img_dataTemp[(i+1)*img_width*4+(j+1)*4 + gg] += quant_error.y() * (1/16.0);
                    img_dataTemp[(i+1)*img_width*4+(j+1)*4 + bb] += quant_error.z() * (1/16.0);
                }
            }
        }else{
            for (int j=img_width - 1; j>=0; j--){
                int offset_rgba = i*img_width*4+j*4;

                /* Floyd–Steinberg dithering algorithm "http://en.wikipedia.org/wiki/Floyd–Steinberg_dithering" */
                QVector3D oldpixel = QVector3D(qBound(0.0f, float(img_dataTemp[offset_rgba + rr]), 255.0f), qBound(0.0f, float(img_dataTemp[offset_rgba + gg]), 255.0f), qBound(0.0f, float(img_dataTemp[offset_rgba + bb]), 255.0f));
                QVector3D newpixel = table[find_closest_palette_color(table, oldpixel)];
                QVector3D quant_error = oldpixel - newpixel;

                img_dataTemp[offset_rgba + rr] = newpixel.x();
                img_dataTemp[offset_rgba + gg] = newpixel.y();
                img_dataTemp[offset_rgba + bb] = newpixel.z();

                if(j-1 >= 0){
                    img_dataTemp[( i )*img_width*4+(j-1)*4 + rr] += quant_error.x() * (7/16.0);
                    img_dataTemp[( i )*img_width*4+(j-1)*4 + gg] += quant_error.y() * (7/16.0);
                    img_dataTemp[( i )*img_width*4+(j-1)*4 + bb] += quant_error.z() * (7/16.0);
                }
                if(i+1 < img_height && j+1 < img_width){
                    img_dataTemp[(i+1)*img_width*4+(j+1)*4 + rr] += quant_error.x() * (3/16.0);
                    img_dataTemp[(i+1)*img_width*4+(j+1)*4 + gg] += quant_error.y() * (3/16.0);
                    img_dataTemp[(i+1)*img_width*4+(j+1)*4 + bb] += quant_error.z() * (3/16.0);
                }
                if(i+1 < img_height){
                    img_dataTemp[(i+1)*img_width*4+( j )*4 + rr] += quant_error.x() * (5/16.0);
                    img_dataTemp[(i+1)*img_width*4+( j )*4 + gg] += quant_error.y() * (5/16.0);
                    img_dataTemp[(i+1)*img_width*4+( j )*4 + bb] += quant_error.z() * (5/16.0);
                }
                if(i+1 < img_height && j-1 >= 0){
                    img_dataTemp[(i+1)*img_width*4+(j-1)*4 + rr] += quant_error.x() * (1/16.0);
                    img_dataTemp[(i+1)*img_width*4+(j-1)*4 + gg] += quant_error.y() * (1/16.0);
                    img_dataTemp[(i+1)*img_width*4+(j-1)*4 + bb] += quant_error.z() * (1/16.0);
                }
            }
        }
    }

    /* img_dataTemp mission complete, do restore */
    for (int i=0; i<img_height; i++)
    {
        for (int j=0; j<img_width; j++)
        {
            int offset_rgba = i*img_width*4+j*4;

            img_data[offset_rgba + rr] = img_dataTemp[offset_rgba + rr];
            img_data[offset_rgba + gg] = img_dataTemp[offset_rgba + gg];
            img_data[offset_rgba + bb] = img_dataTemp[offset_rgba + bb];
        }
    }

    delete[] rgb, img_dataTemp;
	mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
	renew();
}

//------------------------Filter------------------------

///////////////////////////////////////////////////////////////////////////////
//
//     Filtering the img_data array by the filter from the parameters
//
///////////////////////////////////////////////////////////////////////////////
void Application::filtering( double filter[][5] )
{
	unsigned char *rgb = this->To_RGB();
    float count = 0;
    /* if it is edge filter */
    if(filter[0][0] < 0)
        count = 256;
    /* other filter count the tatle average number */
    else
    {
        for (int x=0; x<5; x++)
            for (int y=0; y<5; y++){
                count += filter[x][y];
            }
    }

    for (int i=0; i<img_height; i++)
    {
        for (int j=0; j<img_width; j++)
        {
            int offset_rgba = i*img_width*4+j*4;
            QVector3D averagePixal(0.0f, 0.0f, 0.0f);

            for (int x=-2; x<3; x++)
                for (int y=-2; y<3; y++){
                    if(i+x >= img_height && j+y >= img_width){
                        int offset_rgb = (img_height - ((i+x) - img_height) - 1)*img_width*3+(img_width - ((j+y) - img_width) - 1)*3;
                        averagePixal += filter[x+2][y+2] * (QVector3D(rgb[offset_rgb + rr], rgb[offset_rgb + gg], rgb[offset_rgb + bb]));
                    }else if(i+x >= img_height){
                        int offset_rgb = (img_height - ((i+x) - img_height) - 1)*img_width*3+(qFabs(j+y))*3;
                        averagePixal += filter[x+2][y+2] * (QVector3D(rgb[offset_rgb + rr], rgb[offset_rgb + gg], rgb[offset_rgb + bb]));
                    }else if(j+y >= img_width){
                        int offset_rgb = qFabs(i+x)*img_width*3+(img_width - ((j+y) - img_width))*3;
                        averagePixal += filter[x+2][y+2] * (QVector3D(rgb[offset_rgb + rr], rgb[offset_rgb + gg], rgb[offset_rgb + bb]));
                    }else{
                        int offset_rgb = (qFabs(i+x))*img_width*3+(qFabs(j+y))*3;
                        averagePixal += filter[x+2][y+2] * (QVector3D(rgb[offset_rgb + rr], rgb[offset_rgb + gg], rgb[offset_rgb + bb]));
                    }
                }
            averagePixal /= count;

            img_data[offset_rgba + rr] = qBound(0, (int)averagePixal.x(), 255);
            img_data[offset_rgba + gg] = qBound(0, (int)averagePixal.y(), 255);
            img_data[offset_rgba + bb] = qBound(0, (int)averagePixal.z(), 255);
        }
    }

	delete[] rgb;
	mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
	renew();
}

void Application::filtering(unsigned int **filter, int n )
{
	unsigned char *rgb = this->To_RGB();

    /* count the tatle average number */
    float count = 0;
    for (int x=0; x<n; x++)
        for (int y=0; y<n; y++){
            count += filter[x][y];
        }


    for (int i=0; i<img_height; i++)
    {
        for (int j=0; j<img_width; j++)
        {
            int offset_rgba = i*img_width*4+j*4;
            QVector3D averagePixal(0.0f, 0.0f, 0.0f);

            for (int x=-n/2; x<n-n/2; x++)
                for (int y=-n/2; y<n-n/2; y++){
                    if(i+x >= img_height && j+y >= img_width){
                        int offset_rgb = (img_height - ((i+x) - img_height) - 1)*img_width*3+(img_width - ((j+y) - img_width) - 1)*3;
                        averagePixal += filter[x+n/2][y+n/2] * (QVector3D(rgb[offset_rgb + rr], rgb[offset_rgb + gg], rgb[offset_rgb + bb]));
                    }else if(i+x >= img_height){
                        int offset_rgb = (img_height - ((i+x) - img_height) - 1)*img_width*3+(qFabs(j+y))*3;
                        averagePixal += filter[x+n/2][y+n/2] * (QVector3D(rgb[offset_rgb + rr], rgb[offset_rgb + gg], rgb[offset_rgb + bb]));
                    }else if(j+y >= img_width){
                        int offset_rgb = qFabs(i+x)*img_width*3+(img_width - ((j+y) - img_width))*3;
                        averagePixal += filter[x+n/2][y+n/2] * (QVector3D(rgb[offset_rgb + rr], rgb[offset_rgb + gg], rgb[offset_rgb + bb]));
                    }else{
                        int offset_rgb = (qFabs(i+x))*img_width*3+(qFabs(j+y))*3;
                        averagePixal += filter[x+n/2][y+n/2] * (QVector3D(rgb[offset_rgb + rr], rgb[offset_rgb + gg], rgb[offset_rgb + bb]));
                    }
                }
            averagePixal /= count;
            img_data[offset_rgba + rr] = qBound(0, (int)averagePixal.x(), 255);
            img_data[offset_rgba + gg] = qBound(0, (int)averagePixal.y(), 255);
            img_data[offset_rgba + bb] = qBound(0, (int)averagePixal.z(), 255);
        }
    }

	delete[] rgb;
	mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
	renew();
}
///////////////////////////////////////////////////////////////////////////////
//
//  Perform 5x5 box filter on this image.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
void Application::Filter_Box()
{
    double filter[][5] = {
        0.04, 0.04, 0.04, 0.04, 0.04,
        0.04, 0.04, 0.04, 0.04, 0.04,
        0.04, 0.04, 0.04, 0.04, 0.04,
        0.04, 0.04, 0.04, 0.04, 0.04,
        0.04, 0.04, 0.04, 0.04, 0.04
    };
    filtering(filter);
}
///////////////////////////////////////////////////////////////////////////////
//
//  Perform 5x5 Bartlett filter on this image.  Return success of 
//  operation.
//
///////////////////////////////////////////////////////////////////////////////
void Application::Filter_Bartlett()
{
    double filter[][5] = {
        1, 2, 3, 2, 1,
        2, 4, 6, 4, 2,
        3, 6, 9, 6, 3,
        2, 4, 6, 4, 2,
        1, 2, 3, 2, 1,
    };
    filtering(filter);
}
///////////////////////////////////////////////////////////////////////////////
//
//  Perform 5x5 Gaussian filter on this image.  Return success of 
//  operation.
//
///////////////////////////////////////////////////////////////////////////////
void Application::Filter_Gaussian()
{
    double filter[][5] = {
        1,  4,  6,  4, 1,
        4, 16, 24, 16, 4,
        6, 24, 36, 24, 6,
        4, 16, 24, 16, 4,
        1,  4,  6,  4, 1
    };
    filtering(filter);
}
///////////////////////////////////////////////////////////////////////////////
//
//  Perform NxN Gaussian filter on this image.  Return success of 
//  operation.
//
///////////////////////////////////////////////////////////////////////////////

unsigned int factorial(int k)
{
    unsigned int total = 1;
    for(int i = 1; i <= k; i++)
        total *= i;
    return total;
}

unsigned int C(int n, int k)
{
    return factorial(n) / (factorial(k) * factorial(n-k));
}

void Application::Filter_Gaussian_N( unsigned int N )
{
    unsigned int** filter = new unsigned int*[N];
    for(unsigned int i = 0; i < N; ++i)
        filter[i] = new unsigned int[N];
    /* fill the first row */
    for(unsigned int j = 0, i = N-1; j < N; j++){
       filter[0][j] = C(i, j);
    }
    /* fill the boundary */
    for(unsigned int i = 0; i < N; i++){
        filter[N-1][i] = filter[0][i];
        filter[i][0]   = filter[0][i];
        filter[i][N-1] = filter[0][i];
    }
    /* fill the rest */
    for(unsigned int i = 0; i < N; i++)
        for(unsigned int j = 0; j < N; j++){
        filter[i][j] = filter[i][0] * filter[0][j];
    }
    filtering(filter, N);
    delete[] filter;
}
///////////////////////////////////////////////////////////////////////////////
//
//  Perform 5x5 edge detect (high pass) filter on this image.  Return 
//  success of operation.
//
///////////////////////////////////////////////////////////////////////////////
void Application::Filter_Edge()
{
    double filter[][5] = {
        -1, - 4,  - 6, - 4, -1,
        -4, -16,  -24, -16, -4,
        -6, -24,  220, -24, -6,
        -4, -16,  -24, -16, -4,
        -1, - 4,  - 6, - 4, -1
    };//220 = 256 - 36
    filtering(filter);
}
///////////////////////////////////////////////////////////////////////////////
//
//  Perform a 5x5 enhancement filter to this image.  Return success of 
//  operation.
//
///////////////////////////////////////////////////////////////////////////////
void Application::Filter_Enhance()
{
	unsigned char *rgb = this->To_RGB();

    double filter[][5] = {
        -1, - 4,  - 6, - 4, -1,
        -4, -16,  -24, -16, -4,
        -6, -24,  220, -24, -6,
        -4, -16,  -24, -16, -4,
        -1, - 4,  - 6, - 4, -1
    };

    float count = 256;


    for (int i=0; i<img_height; i++)
    {
        for (int j=0; j<img_width; j++)
        {
            int offset_rgba = i*img_width*4+j*4;
            QVector3D averagePixal(0.0f, 0.0f, 0.0f);

            for (int x=-2; x<3; x++)
                for (int y=-2; y<3; y++){
                    if(i+x >= img_height && j+y >= img_width){
                        int offset_rgb = (img_height - ((i+x) - img_height) - 1)*img_width*3+(img_width - ((j+y) - img_width) - 1)*3;
                        averagePixal += filter[x+2][y+2] * (QVector3D(rgb[offset_rgb + rr], rgb[offset_rgb + gg], rgb[offset_rgb + bb]));
                    }else if(i+x >= img_height){
                        int offset_rgb = (img_height - ((i+x) - img_height) - 1)*img_width*3+(qFabs(j+y))*3;
                        averagePixal += filter[x+2][y+2] * (QVector3D(rgb[offset_rgb + rr], rgb[offset_rgb + gg], rgb[offset_rgb + bb]));
                    }else if(j+y >= img_width){
                        int offset_rgb = qFabs(i+x)*img_width*3+(img_width - ((j+y) - img_width))*3;
                        averagePixal += filter[x+2][y+2] * (QVector3D(rgb[offset_rgb + rr], rgb[offset_rgb + gg], rgb[offset_rgb + bb]));
                    }else{
                        int offset_rgb = (qFabs(i+x))*img_width*3+(qFabs(j+y))*3;
                        averagePixal += filter[x+2][y+2] * (QVector3D(rgb[offset_rgb + rr], rgb[offset_rgb + gg], rgb[offset_rgb + bb]));
                    }
                }
            averagePixal /= count;
            /* image += High-Pass; */
            img_data[offset_rgba + rr] = qBound(0, img_data[offset_rgba + rr] + qBound(0, (int)averagePixal.x(), 255), 255);
            img_data[offset_rgba + gg] = qBound(0, img_data[offset_rgba + gg] + qBound(0, (int)averagePixal.y(), 255), 255);
            img_data[offset_rgba + bb] = qBound(0, img_data[offset_rgba + bb] + qBound(0, (int)averagePixal.z(), 255), 255);
        }
    }

	delete[] rgb;
	mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
	renew();
}

//------------------------Size------------------------

///////////////////////////////////////////////////////////////////////////////
//
//  Halve the dimensions of this image.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
void Application::Half_Size()
{
    unsigned char* rgb = this->To_RGB();
    unsigned char* newImgData = new unsigned char[img_height*img_width/2/2*32];
    double filter[][3] = {
        1/16.0, 1/8.0, 1/16.0,
        1/ 8.0, 1/4.0, 1/ 8.0,
        1/16.0, 1/8.0, 1/16.0
    };

    for (int i=0; i<img_height/2; i++)
    {
        for (int j=0; j<img_width/2; j++)
        {
            int offset_rgba = i*img_width/2*4+j*4;
            QVector3D averagePixal(0.0f, 0.0f, 0.0f);

            for (int x=-1; x<2; x++)
                for (int y=-1; y<2; y++){
                    int offset_rgb = (qFabs(2*i+x))*img_width*3+(qFabs(2*j+y))*3;

                    averagePixal += filter[x+1][y+1] * (QVector3D(rgb[offset_rgb + rr], rgb[offset_rgb + gg], rgb[offset_rgb + bb]));
                }
            newImgData[offset_rgba + rr] = qBound(0, (int)averagePixal.x(), 255);
            newImgData[offset_rgba + gg] = qBound(0, (int)averagePixal.y(), 255);
            newImgData[offset_rgba + bb] = qBound(0, (int)averagePixal.z(), 255);
            newImgData[offset_rgba + aa] = 255;
        }
    }
    img_height /= 2;
    img_width  /= 2;
    img_data = newImgData;
    delete[] rgb, newImgData;
    mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
	renew();
}
///////////////////////////////////////////////////////////////////////////////
//
//  Double the dimensions of this image.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
void Application::Double_Size()
{
    Resize(2);
}
///////////////////////////////////////////////////////////////////////////////
//
//  resample_src for resize and rotate
//
///////////////////////////////////////////////////////////////////////////////
QVector3D Application::resample_src(int u, int v, unsigned char* rgb)
{
    if(u < 0 || v < 0 || u >= img_height || v >= img_width) return QVector3D(0, 0, 0);
    int offset_rgb = u*img_width*3+v*3;
    return QVector3D(rgb[offset_rgb + rr], rgb[offset_rgb + gg], rgb[offset_rgb + bb]);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Scale the image dimensions by the given factor.  The given factor is 
//	assumed to be greater than one.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
void Application::Resize( float scale )
{
    unsigned char* rgb = this->To_RGB();
    unsigned char* newImgData = new unsigned char[img_height*img_width*scale*scale*32];

    for (int i=0; i<img_height*scale; i++)
    {
        for (int j=0; j<img_width*scale; j++)
        {
            int offset_rgba = i*img_width*scale*4+j*4;
            int u = i/scale;
            int v = j/scale;

            QVector3D dst = resample_src(u, v, rgb);

            newImgData[offset_rgba + rr] = qBound(0, (int)dst.x(), 255);
            newImgData[offset_rgba + gg] = qBound(0, (int)dst.y(), 255);
            newImgData[offset_rgba + bb] = qBound(0, (int)dst.z(), 255);
            newImgData[offset_rgba + aa] = 255;
        }
    }
    img_height *= scale;
    img_width  *= scale;
    img_data = newImgData;
    delete[] rgb, newImgData;
    mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
    renew();
}

//////////////////////////////////////////////////////////////////////////////
//
//  Rotate the image clockwise by the given angle.  Do not resize the 
//  image.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
void Application::Rotate( float angleDegrees )
{
    unsigned char* rgb = this->To_RGB();
    unsigned char* newImgData = new unsigned char[img_height*img_width*32];

    angleDegrees = qDegreesToRadians(angleDegrees);

    for (int i=0; i<img_height; i++)
    {
        for (int j=0; j<img_width; j++)
        {
            int offset_rgba = i*img_width*4+j*4;
            int u = i*cos(angleDegrees) - j*sin(angleDegrees);
            int v = i*sin(angleDegrees) + j*cos(angleDegrees);

            QVector3D dst = resample_src(u, v, rgb);

            newImgData[offset_rgba + rr] = qBound(0, (int)dst.x(), 255);
            newImgData[offset_rgba + gg] = qBound(0, (int)dst.y(), 255);
            newImgData[offset_rgba + bb] = qBound(0, (int)dst.z(), 255);
            newImgData[offset_rgba + aa] = 255;
        }
    }

    mImageDst = QImage(newImgData, img_width, img_height, QImage::Format_ARGB32 );
    delete[] rgb, newImgData;
	renew();
}

//------------------------Composing------------------------


void Application::loadSecondaryImge( QString filePath )
{
	mImageSrcSecond.load(filePath);

	renew();

	img_data2 = mImageSrcSecond.bits();
	img_width2 = mImageSrcSecond.width();
	img_height2 = mImageSrcSecond.height();
}

///////////////////////////////////////////////////////////////////////////////
//
//      Composite the current image over the given image.  Return success of 
//  operation.
//
///////////////////////////////////////////////////////////////////////////////
void Application::Comp_Over()
{
	if (img_height == img_height2 && img_width == img_width2)
	{
        unsigned char* newImgData = new unsigned char[img_height*img_width*32];

        for (int i=0; i<img_height; i++)
        {
            for (int j=0; j<img_width; j++)
            {
                int offset_rgba = i*img_width*4+j*4;

                float FA = 1, FB = 1 - img_data[offset_rgba + aa] / 256.0;

                QVector3D img1(img_data [offset_rgba + rr], img_data [offset_rgba + gg], img_data [offset_rgba + bb]);
                QVector3D img2(img_data2[offset_rgba + rr], img_data2[offset_rgba + gg], img_data2[offset_rgba + bb]);

                img1 *= img_data [offset_rgba + aa] / 256.0;
                img2 *= img_data2[offset_rgba + aa] / 256.0;

                QVector3D result = img1 * FA + img2 * FB;

                newImgData[offset_rgba + rr] = qBound(0, (int)result.x(), 255);
                newImgData[offset_rgba + gg] = qBound(0, (int)result.y(), 255);
                newImgData[offset_rgba + bb] = qBound(0, (int)result.z(), 255);
                newImgData[offset_rgba + aa] = qBound(0, (int)(FA * img_data[offset_rgba + aa] + FB * img_data2[offset_rgba + aa]), 255);
            }
        }
        img_data = newImgData;
        delete[] newImgData;
        mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
        renew();
	}
	else
	{
		std::cout << "Images not the same size" << std::endl;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
//      Composite this image "in" the given image.  See lecture notes for 
//  details.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
void Application::Comp_In()
{
	if (img_height == img_height2 && img_width == img_width2)
	{
        unsigned char* newImgData = new unsigned char[img_height*img_width*32];

        for (int i=0; i<img_height; i++)
        {
            for (int j=0; j<img_width; j++)
            {
                int offset_rgba = i*img_width*4+j*4;

                float FA = img_data2[offset_rgba + aa] / 256.0, FB = 0;

                QVector3D img1(img_data [offset_rgba + rr], img_data [offset_rgba + gg], img_data [offset_rgba + bb]);
                QVector3D img2(img_data2[offset_rgba + rr], img_data2[offset_rgba + gg], img_data2[offset_rgba + bb]);

                img1 *= img_data [offset_rgba + aa] / 256.0;
                img2 *= img_data2[offset_rgba + aa] / 256.0;

                QVector3D result = img1 * FA + img2 * FB;

                newImgData[offset_rgba + rr] = qBound(0, (int)result.x(), 255);
                newImgData[offset_rgba + gg] = qBound(0, (int)result.y(), 255);
                newImgData[offset_rgba + bb] = qBound(0, (int)result.z(), 255);
                newImgData[offset_rgba + aa] = qBound(0, (int)(FA * img_data[offset_rgba + aa] + FB * img_data2[offset_rgba + aa]), 255);
            }
        }

        img_data = newImgData;
        delete[] newImgData;
        mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
        renew();
	}
	else
	{
		std::cout << "Images not the same size" << std::endl;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
//      Composite this image "out" the given image.  See lecture notes for 
//  details.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
void Application::Comp_Out()
{
	if (img_height == img_height2 && img_width == img_width2)
	{
        unsigned char* newImgData = new unsigned char[img_height*img_width*32];

        for (int i=0; i<img_height; i++)
        {
            for (int j=0; j<img_width; j++)
            {
                int offset_rgba = i*img_width*4+j*4;

                float FA = 1 - img_data2[offset_rgba + aa] / 256.0, FB = 0;

                QVector3D img1(img_data [offset_rgba + rr], img_data [offset_rgba + gg], img_data [offset_rgba + bb]);
                QVector3D img2(img_data2[offset_rgba + rr], img_data2[offset_rgba + gg], img_data2[offset_rgba + bb]);

                img1 *= img_data [offset_rgba + aa] / 256.0;
                img2 *= img_data2[offset_rgba + aa] / 256.0;

                QVector3D result = img1 * FA + img2 * FB;

                newImgData[offset_rgba + rr] = qBound(0, (int)result.x(), 255);
                newImgData[offset_rgba + gg] = qBound(0, (int)result.y(), 255);
                newImgData[offset_rgba + bb] = qBound(0, (int)result.z(), 255);
                newImgData[offset_rgba + aa] = qBound(0, (int)(FA * img_data[offset_rgba + aa] + FB * img_data2[offset_rgba + aa]), 255);
            }
        }

        img_data = newImgData;
        delete[] newImgData;
        mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
        renew();
	}
	else
	{
		std::cout << "Images not the same size" << std::endl;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
//      Composite current image "atop" given image.  Return success of 
//  operation.
//
///////////////////////////////////////////////////////////////////////////////
void Application::Comp_Atop()
{
	if (img_height == img_height2 && img_width == img_width2)
	{
        unsigned char* newImgData = new unsigned char[img_height*img_width*32];

        for (int i=0; i<img_height; i++)
        {
            for (int j=0; j<img_width; j++)
            {
                int offset_rgba = i*img_width*4+j*4;

                float FA = img_data2[offset_rgba + aa], FB = 1 - img_data[offset_rgba + aa] / 256.0;

                QVector3D img1(img_data [offset_rgba + rr], img_data [offset_rgba + gg], img_data [offset_rgba + bb]);
                QVector3D img2(img_data2[offset_rgba + rr], img_data2[offset_rgba + gg], img_data2[offset_rgba + bb]);

                img1 *= img_data [offset_rgba + aa] / 256.0;
                img2 *= img_data2[offset_rgba + aa] / 256.0;

                QVector3D result = img1 * FA + img2 * FB;

                newImgData[offset_rgba + rr] = qBound(0, (int)result.x(), 255);
                newImgData[offset_rgba + gg] = qBound(0, (int)result.y(), 255);
                newImgData[offset_rgba + bb] = qBound(0, (int)result.z(), 255);
                newImgData[offset_rgba + aa] = qBound(0, (int)(FA * img_data[offset_rgba + aa] + FB * img_data2[offset_rgba + aa]), 255);
            }
        }

        img_data = newImgData;
        delete[] newImgData;
        mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
        renew();
	}
	else
	{
		std::cout << "Images not the same size" << std::endl;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
//      Composite this image with given image using exclusive or (XOR).  Return
//  success of operation.
//
///////////////////////////////////////////////////////////////////////////////
void Application::Comp_Xor()
{
	if (img_height == img_height2 && img_width == img_width2)
	{
        unsigned char* newImgData = new unsigned char[img_height*img_width*32];

        for (int i=0; i<img_height; i++)
        {
            for (int j=0; j<img_width; j++)
            {
                int offset_rgba = i*img_width*4+j*4;

                float FA = 1 - img_data2[offset_rgba + aa] / 256.0, FB = 1 - img_data[offset_rgba + aa] / 256.0;

                QVector3D img1(img_data [offset_rgba + rr], img_data [offset_rgba + gg], img_data [offset_rgba + bb]);
                QVector3D img2(img_data2[offset_rgba + rr], img_data2[offset_rgba + gg], img_data2[offset_rgba + bb]);

                img1 *= img_data [offset_rgba + aa] / 256.0;
                img2 *= img_data2[offset_rgba + aa] / 256.0;

                QVector3D result = img1 * FA + img2 * FB;

                newImgData[offset_rgba + rr] = qBound(0, (int)result.x(), 255);
                newImgData[offset_rgba + gg] = qBound(0, (int)result.y(), 255);
                newImgData[offset_rgba + bb] = qBound(0, (int)result.z(), 255);
                newImgData[offset_rgba + aa] = qBound(0, (int)(FA * img_data[offset_rgba + aa] + FB * img_data2[offset_rgba + aa]), 255);
            }
        }

        img_data = newImgData;
        delete[] newImgData;
        mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
        renew();
	}
	else
	{
		std::cout << "Images not the same size" << std::endl;
	}
}

//------------------------NPR------------------------

///////////////////////////////////////////////////////////////////////////////
//
//      Run simplified version of Hertzmann's painterly image filter.
//      You probably will want to use the Draw_Stroke funciton and the
//      Stroke class to help.
// Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
void Application::NPR_Paint()
{
    unsigned char *tReferenceImage = new unsigned char[img_height*img_width*32];
    unsigned char *sourceImage     = new unsigned char[img_height*img_width*32];
    int tBrushSize;
    for (int i=0; i<img_height; i++)
    {
        for (int j=0; j<img_width; j++)
        {
            int offset_rgba = i*img_width*4+j*4;

            /* sorceImage is the backup of img_data */
            sourceImage[offset_rgba + rr] = img_data[offset_rgba + rr];
            sourceImage[offset_rgba + gg] = img_data[offset_rgba + gg];
            sourceImage[offset_rgba + bb] = img_data[offset_rgba + bb];
            sourceImage[offset_rgba + aa] = img_data[offset_rgba + aa];

            img_data[offset_rgba + rr] = img_data[offset_rgba + gg] = img_data[offset_rgba + bb] = img_data[offset_rgba + aa] = WHITE;
        }
    }

    /* do Gaussian blur with brush size = 10 */
    tBrushSize = 10;

    for (int i = 0; i < img_height; i++)
    {
        for (int j = 0; j < img_width; j++)
        {
            int offset_rgba = i*img_width*4+j*4;

            tReferenceImage[offset_rgba + rr] = sourceImage[offset_rgba + rr];
            tReferenceImage[offset_rgba + gg] = sourceImage[offset_rgba + gg];
            tReferenceImage[offset_rgba + bb] = sourceImage[offset_rgba + bb];
            tReferenceImage[offset_rgba + aa] = sourceImage[offset_rgba + aa];
        }
    }

    NPR_Paint_Layer(img_data, tReferenceImage, tBrushSize);

    /* do Gaussian blur with brush size = 2 */
    tBrushSize = 2;

    for (int i = 0; i < img_height; i++)
    {
        for (int j = 0; j < img_width; j++)
        {
            int offset_rgba = i*img_width*4+j*4;

            tReferenceImage[offset_rgba + rr] = sourceImage[offset_rgba + rr];
            tReferenceImage[offset_rgba + gg] = sourceImage[offset_rgba + gg];
            tReferenceImage[offset_rgba + bb] = sourceImage[offset_rgba + bb];
            tReferenceImage[offset_rgba + aa] = sourceImage[offset_rgba + aa];
        }
    }

    NPR_Paint_Layer(img_data, tReferenceImage, tBrushSize);

    mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
	renew();
}

float difference(QVector3D canvas, QVector3D referenceImage)
{
    return canvas.distanceToPoint(referenceImage);
}

void Application::NPR_Paint_Layer( unsigned char *tCanvas, unsigned char *tReferenceImage, int tBrushSize )
{
    /* D is distance from every canvas pixal to every referenceimage pixal */
    float** D = new float* [img_height];
    for(int i = 0; i < img_height; i++)
        D[i] = new float[img_width];

    for (int i=0; i<img_height; i++)
    {
        for (int j=0; j<img_width; j++)
        {
            int offset_rgba = i*img_width*4+j*4;

            QVector3D canvas(tCanvas[offset_rgba + rr], tCanvas[offset_rgba + gg], tCanvas[offset_rgba + bb]);
            QVector3D referenceImage(tReferenceImage[offset_rgba + rr], tReferenceImage[offset_rgba + gg], tReferenceImage[offset_rgba + bb]);
            D[i][j] = difference(canvas, referenceImage);
        }
    }

    for (int i = 0; i < img_height - tBrushSize; i += tBrushSize/2)
    {
        for (int j = 0; j < img_width - tBrushSize; j += tBrushSize/2)
        {
            int offset_rgba = i*img_width*4+j*4;
            float areaError = 0;
            QVector3D largestErrorPoint(0, 0, 0); // largestErrorPoint(pixalX, pixalY, length from canvas[Y][X] to referenceImage[Y][X])

            for(int x = i; x < i + tBrushSize; x++){
                for(int y = j; y < j + tBrushSize; y++){
                    areaError += D[x][y];
                    if(largestErrorPoint.z() < D[x][y]){
                        largestErrorPoint.setX(x);
                        largestErrorPoint.setY(y);
                        largestErrorPoint.setZ(D[x][y]);
                    }
                }
            }

            areaError /= tBrushSize * tBrushSize;

            /* set high-pass edge = 25 */
            if(areaError > 25){
                Paint_Stroke(Stroke(tBrushSize, largestErrorPoint.y(), largestErrorPoint.x(), tReferenceImage[offset_rgba + rr], tReferenceImage[offset_rgba + gg], tReferenceImage[offset_rgba + bb], tReferenceImage[offset_rgba + aa]));
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//
//      Helper function for the painterly filter; paint a stroke at
// the given location
//
///////////////////////////////////////////////////////////////////////////////
void Application::Paint_Stroke( const Stroke& s )
{
	int radius_squared = (int)s.radius * (int)s.radius;
	for (int x_off = -((int)s.radius); x_off <= (int)s.radius; x_off++) 
	{
		for (int y_off = -((int)s.radius); y_off <= (int)s.radius; y_off++) 
		{
			int x_loc = (int)s.x + x_off;
			int y_loc = (int)s.y + y_off;

			// are we inside the circle, and inside the image?
			if ((x_loc >= 0 && x_loc < img_width && y_loc >= 0 && y_loc < img_height)) 
			{
				int dist_squared = x_off * x_off + y_off * y_off;
				int offset_rgba = (y_loc * img_width + x_loc) * 4;

				if (dist_squared <= radius_squared) 
				{
					img_data[offset_rgba + rr] = s.r;
					img_data[offset_rgba + gg] = s.g;
					img_data[offset_rgba + bb] = s.b;
					img_data[offset_rgba + aa] = s.a;
				} 
				else if (dist_squared == radius_squared + 1) 
				{
					img_data[offset_rgba + rr] = (img_data[offset_rgba + rr] + s.r) / 2;
					img_data[offset_rgba + gg] = (img_data[offset_rgba + gg] + s.g) / 2;
					img_data[offset_rgba + bb] = (img_data[offset_rgba + bb] + s.b) / 2;
					img_data[offset_rgba + aa] = (img_data[offset_rgba + aa] + s.a) / 2;
				}
			}
		}
	}
}





///////////////////////////////////////////////////////////////////////////////
//
//      Build a Stroke
//
///////////////////////////////////////////////////////////////////////////////
Stroke::Stroke() {}

///////////////////////////////////////////////////////////////////////////////
//
//      Build a Stroke
//
///////////////////////////////////////////////////////////////////////////////
Stroke::Stroke(unsigned int iradius, unsigned int ix, unsigned int iy,
	unsigned char ir, unsigned char ig, unsigned char ib, unsigned char ia) :
radius(iradius),x(ix),y(iy),r(ir),g(ig),b(ib),a(ia)
{
}

///////////////////////////////////////////////////////////////////////////////
//
//      Brightness Change
//
///////////////////////////////////////////////////////////////////////////////

void Application::BrightnessChange(int delta)
{
    unsigned char *rgb = this->To_RGB();

    for (int i=0; i<img_height; i++)
    {
        for (int j=0; j<img_width; j++)
        {
            int offset_rgb = i*img_width*3+j*3;
            int offset_rgba = i*img_width*4+j*4;

            img_data[offset_rgba + rr] = qBound(0, rgb[offset_rgb + rr] + delta, 255);
            img_data[offset_rgba + gg] = qBound(0, rgb[offset_rgb + gg] + delta, 255);
            img_data[offset_rgba + bb] = qBound(0, rgb[offset_rgb + bb] + delta, 255);
        }
    }

    delete[] rgb;
    mImageDst = QImage(img_data, img_width, img_height, QImage::Format_ARGB32 );
    renew();
}
