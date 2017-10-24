#include <iostream>
#include <fstream>

//#include "fftw3.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

//#include "LBPGPU.cuh"

#ifndef _LBP_H_
#define _LBP_H_

#ifndef NULL
#define NULL 0
#endif

// SWIG doesn't understand 'using' directives properly
// so disable them if doing the SWIG pass
#ifndef SWIG
using namespace std;
using namespace cv;
#endif
/*
// enable/disable use of mixed OpenCV API in the code below.
#define DEMO_MIXED_API_USE 0
#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
( std::ostringstream() << std::dec << x ) ).str()
*/
namespace lbp {
    
	enum MappingType {
		LBP_MAPPING_NONE = 0,
		LBP_MAPPING_U2,
		LBP_MAPPING_RI,
		LBP_MAPPING_RIU2,
		LBP_MAPPING_HF
	};
    
	static const string MappingTypeStr[] = {
				"none", "u2", "ri", "riu2", "hf" };
    
	class LBP {
        
	public:
		LBP();
		LBP( unsigned int samples, MappingType type );
		LBP(unsigned int samples);
		LBP(unsigned int samples, string mapping);
		//LBP & LBP::associateTableMapping(unsigned int sampless);
		void LBP::associateTableMapping(unsigned int sampless,string mapping);
		~LBP( void );
        
		/**
		 * Mapping methods
		 */
		LBP & generateMapping();
		LBP & generateMapping( unsigned int samples, MappingType type );
		//LBP & LBP::associateTableMapping(unsigned int samples, int NumTable);

		bool saveMapping( string fileName );
		//bool loadMapping( string fileName );
		bool LBP::loadMapping(string fileName, int num);
        
        static MappingType strToType( string s ) {
            
            if( s.compare( "u2" ) == 0 )
                return LBP_MAPPING_U2;
            else if( s.compare("ri") == 0 )
                return LBP_MAPPING_RI;
            else if ( s.compare("riu2") == 0 )
                return LBP_MAPPING_RIU2;
            else if( s.compare("hf")  == 0 )
                return LBP_MAPPING_HF;
            else
                return LBP_MAPPING_NONE;
        }
        
        MappingType getMapping(void) const {
        	return type;
        }

		/**
		 * Descriptor methods
		 */
/*        void calcGPU( Mat img, double radius = 1. ) {
        	unsigned char * src;
        	unsigned char * dst;
//        	LBPMapping mapping;
//        	calcLBPGPU( src, dst, 10, 10, &mapping );
        }
		*/
		LBP & calcLBP( Mat img, int numTable,double radius = 1., bool borderCopy=false);
//		Mat LBP::LbpInit(LBP lbp, Mat img, int rad);


		Mat getLBPImage( void ) const {
			return lbpImage;
		}
        // AGGIUNTO:
		void setLBPImage(Mat tmp)  {
			lbpImage=tmp;
		}

		void set_num(int tmp) {
			num = tmp;
		}
		
		void set_samples(int tmp) {
			samples = tmp;
		}

		bool saveLBPImage( string fileName );
		/**
		 * Histogram methods
		 */
		LBP & calcHist(void);
		LBP & calcHist( Mat mask );

		vector<double> getHist( bool norm = true );
		//vector<double> constructHF( vector<double> h );
        
        
		/**
		 * Other methods
		 */
		//std::string toString( bool verbose=false ) const;
        
	private:
        // Mapping variables
        MappingType type;
		vector<int> *table;
        vector<int> table_8;
		vector<int> table_16;
        unsigned int samples=NULL;
        unsigned int num;
        // Fourier Histogram variables
        vector< vector<int> > orbits;
        //double *fftIn;
        //complex<double> *fftOut;
        //fftw_plan fftPlan;
        //unsigned int fftN;
        //unsigned int fftHermN;
        //vector<double> hf;
        // Histogram
        vector<double> h;
        // Descriptor variables
        Mat lbpImage;
        MatND hist;
        
        // Private bit operation methods
        int NumberOfSetBits( int i ) {
            i = i - ((i >> 1) & 0x55555555);
            i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
            return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
        }
        unsigned int rotateLeft( unsigned int i, unsigned int samples ) {
            unsigned int bg = ((i & (1 << (samples - 1))) >> (samples - 1)); // bitget(r,samples)
            unsigned int bs = (i << 1) & ((int) pow( 2., (int) samples ) - 1); // bitshift(r, 1, samples)
            unsigned int j = (bs + bg) & ((int) pow( 2., (int) samples ) - 1); // bitset( bs, 1, bg )
            return j;
        }
        int trailingZeroInd( int v ) {  // find the number of trailing zeros in v
            static const int Mod37BitPosition[] =  // map a bit value mod 37 to its position
            { 32, 0, 1, 26, 2, 23, 27, 0, 3, 16, 24, 30, 28, 11, 0, 13, 4, 7, 17, 0, 25,
                22, 31, 15, 29, 10, 12, 6, 0, 21, 14, 9, 5, 20, 8, 19, 18 };
            return Mod37BitPosition[(-v & v) % 37];
        }
        
//        void initHF(void);

        LBP & calcHist( Mat * img, Mat * mask=NULL );
	};
    
}
;

#endif
