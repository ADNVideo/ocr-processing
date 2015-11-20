/**
 * Functions to Convert beetween different charset
 * author Julien Folly
 * version 1.0
 */

#include <charset.h>
#include <stdio.h>
#include <stdlib.h>

#define ASCII               0x7f    // 7 Bits
#define ISO_8859            0xff    // 8 Bits

#define UTF8_MAX_IN_1       0x7f     //  7 bits (2^7-1)
#define UTF8_MAX_IN_2       0x7ff    // 11 bits (2^11-1)
#define UTF8_MAX_IN_3       0xffff   // 16 bits (2^16-1)

#define UTF8_1ST_OF_1       0     // 0xxx xxxx
#define UTF8_1ST_OF_2       0xc0  // 110x xxxx
#define UTF8_1ST_OF_3       0xe0  // 1110 xxxx
#define UTF8_TRAIL          0x80  // 10xx xxxx

/**
 * Convert from Extended ascii to ISO 8859-1
 * Return iSrcLen, DEST_TOO_SMALL if the destination is too small, or
 * INCOMPATIBLE_EASCII if it's impossible to convert from eascii to ios8835
 * The iDestLen should be equal to iSrcLen
 *
 * capSrc    ->    Pointer to the string to convert
 * iSrcLen   ->    Number of character in capSrc
 * capDest   ->    Pointer to an allocated memory area for the converted string
 * iDestLen  ->    Size of the allocated memory area
 */
unsigned int easciiToIso8859(const char * capSrc,unsigned int iSrcLen,char * capDest,unsigned int iDestLen){
    if(iDestLen < iSrcLen) return DEST_TOO_SMALL;
    unsigned int i,ret = iSrcLen;
    
    for(i = 0 ; i<iSrcLen ; ++i){
        switch((unsigned char)capSrc[i]){
            case 0x80: capDest[i] = 0xC7; break;
            case 0x81: capDest[i] = 0xFC; break;
            case 0x82: capDest[i] = 0xE9; break;
            case 0x83: capDest[i] = 0xE2; break;
            case 0x84: capDest[i] = 0xE4; break;
            case 0x85: capDest[i] = 0xE0; break;
            case 0x86: capDest[i] = 0xE5; break;
            case 0x87: capDest[i] = 0xE7; break;
            case 0x88: capDest[i] = 0xEA; break;
            case 0x89: capDest[i] = 0xEB; break;
            case 0x8A: capDest[i] = 0xE8; break;
            case 0x8B: capDest[i] = 0xEF; break;
            case 0x8C: capDest[i] = 0xEE; break;
            case 0x8D: capDest[i] = 0xEC; break;
            case 0x8E: capDest[i] = 0xC4; break;
            case 0x8F: capDest[i] = 0xC5; break;
            case 0x90: capDest[i] = 0xC9; break;
            case 0x91: capDest[i] = 0xE6; break;
            case 0x92: capDest[i] = 0xC6; break;
            case 0x93: capDest[i] = 0xF4; break;
            case 0x94: capDest[i] = 0xF6; break;
            case 0x95: capDest[i] = 0xF2; break;
            case 0x96: capDest[i] = 0xFB; break;
            case 0x97: capDest[i] = 0xF9; break;
            case 0x98: capDest[i] = 0xFF; break;
            case 0x99: capDest[i] = 0xD6; break;
            case 0x9A: capDest[i] = 0xDC; break;
            case 0x9B: capDest[i] = 0xF8; break;
            case 0x9C: capDest[i] = 0xA3; break;
            case 0x9D: capDest[i] = 0xD8; break;
            case 0x9E: capDest[i] = 0xD7; break;
            case 0xA0: capDest[i] = 0xE1; break;
            case 0xA1: capDest[i] = 0xED; break;
            case 0xA2: capDest[i] = 0xF3; break;
            case 0xA3: capDest[i] = 0xFA; break;
            case 0xA4: capDest[i] = 0xF1; break;
            case 0xA5: capDest[i] = 0xD1; break;
            case 0xA6: capDest[i] = 0xAA; break;
            case 0xA7: capDest[i] = 0xBA; break;
            case 0xA8: capDest[i] = 0xBF; break;
            case 0xA9: capDest[i] = 0xAE; break;
            case 0xAA: capDest[i] = 0xAC; break;
            case 0xAB: capDest[i] = 0xBD; break;
            case 0xAC: capDest[i] = 0xBC; break;
            case 0xAD: capDest[i] = 0xA1; break;
            case 0xAE: capDest[i] = 0xAB; break;
            case 0xAF: capDest[i] = 0xBB; break;
            case 0xB5: capDest[i] = 0xC1; break;
            case 0xB6: capDest[i] = 0xC2; break;
            case 0xB7: capDest[i] = 0xC0; break;
            case 0xB8: capDest[i] = 0xA9; break;
            case 0xBD: capDest[i] = 0xA2; break;
            case 0xBE: capDest[i] = 0xA5; break;
            case 0xC6: capDest[i] = 0xE3; break;
            case 0xC7: capDest[i] = 0xC3; break;
            case 0xCF: capDest[i] = 0xA4; break;
            case 0xD0: capDest[i] = 0xF0; break;
            case 0xD1: capDest[i] = 0xD0; break;
            case 0xD2: capDest[i] = 0xCA; break;
            case 0xD3: capDest[i] = 0xCB; break;
            case 0xD4: capDest[i] = 0xC8; break;
            case 0xD6: capDest[i] = 0xCD; break;
            case 0xD7: capDest[i] = 0xCE; break;
            case 0xD8: capDest[i] = 0xCF; break;
            case 0xDD: capDest[i] = 0xA6; break;
            case 0xDE: capDest[i] = 0xCC; break;
            case 0xE0: capDest[i] = 0xD3; break;
            case 0xE1: capDest[i] = 0xDF; break;
            case 0xE2: capDest[i] = 0xD4; break;
            case 0xE3: capDest[i] = 0xD2; break;
            case 0xE4: capDest[i] = 0xF5; break;
            case 0xE5: capDest[i] = 0xD5; break;
            case 0xE6: capDest[i] = 0xB5; break;
            case 0xE7: capDest[i] = 0xDE; break;
            case 0xE8: capDest[i] = 0xFE; break;
            case 0xE9: capDest[i] = 0xDA; break;
            case 0xEA: capDest[i] = 0xDB; break;
            case 0xEB: capDest[i] = 0xD9; break;
            case 0xEC: capDest[i] = 0xFD; break;
            case 0xED: capDest[i] = 0xDD; break;
            case 0xEE: capDest[i] = 0xAF; break;
            case 0xEF: capDest[i] = 0xB4; break;
            case 0xF0: capDest[i] = 0xAD; break;
            case 0xF1: capDest[i] = 0xB1; break;
            case 0xF3: capDest[i] = 0xBE; break;
            case 0xF4: capDest[i] = 0xB6; break;
            case 0xF5: capDest[i] = 0xA7; break;
            case 0xF6: capDest[i] = 0xF7; break;
            case 0xF7: capDest[i] = 0xB8; break;
            case 0xF8: capDest[i] = 0xB0; break;
            case 0xF9: capDest[i] = 0xA8; break;
            case 0xFA: capDest[i] = 0xB7; break;
            case 0xFB: capDest[i] = 0xB9; break;
            case 0xFC: capDest[i] = 0xB3; break;
            case 0xFD: capDest[i] = 0xB2; break;
            
            default:
                if((unsigned char)capSrc[i] > ASCII) ret = INCOMPATIBLE_EASCII;
                capDest[i] = capSrc[i];
        }   
    } 
    return ret;
}
    
/**
 * Convert from ISO 8859-1 to Unicode
 * Return iSrcLen or DEST_TOO_SMALL if the destination is too small
 * The iDestLen should be equal to iSrcLen
 *
 * capSrc    ->    Pointer to the string to convert
 * iSrcLen   ->    Number of character in capSrc
 * wcapDest  ->    Pointer to an allocated memory area for the converted string
 * iDestLen  ->    Size of the allocated memory area
 */
unsigned int iso8859ToUnicode(const char * capSrc,unsigned int iSrcLen,wchar * wcapDest,unsigned int iDestLen){
    if(iDestLen < iSrcLen) return DEST_TOO_SMALL;
    unsigned int i;
    
    for(i = 0 ; i<iSrcLen ; ++i)
        wcapDest[i] = capSrc[i] & ISO_8859;
    return iSrcLen;
}

/**
 * Convert from unicode to UTF8
 * Return the number of UTF8 byte or DEST_TOO_SMALL if the destination is too small
 * The iDestLen should be at maximum 3 * iSrcLen
 *
 * wcapSrc   ->    Pointer to the string to convert
 * iSrcLen   ->    Number of character in capSrc
 * capDest   ->    Pointer to an allocated memory area for the converted string
 * iDestLen  ->    Size of the allocated memory area
 */
unsigned int unicodeToUtf8(const wchar * wcapSrc,unsigned int iSrcLen,char * capDest,unsigned int iDestLen){
    if(iDestLen == 0) return DEST_TOO_SMALL;
    unsigned int iNbUTF8 = 0;
    unsigned int i;
    
    for(i = 0 ; i<iSrcLen ; ++i){
        
        // Found 1 bits sequence (ASCII)
        if(wcapSrc[i] <= UTF8_MAX_IN_1){
            capDest[iNbUTF8++] = wcapSrc[i];
            if(iNbUTF8 > iDestLen) return DEST_TOO_SMALL;
        }else
        
        // Found 2 bits sequence
        if(wcapSrc[i] <= UTF8_MAX_IN_2){
            capDest[iNbUTF8++] = UTF8_1ST_OF_2 | (wcapSrc[i] >> 6  );
            if(iNbUTF8 > iDestLen) return DEST_TOO_SMALL;
            
            capDest[iNbUTF8++] = UTF8_TRAIL      | (wcapSrc[i] & 0x3F);
            if(iNbUTF8 > iDestLen) return DEST_TOO_SMALL;
        }else
        
        // Found 3 bits sequence
        /* if(wcapSrc[i] <= UTF8_MAX_IN_3) */{
            capDest[iNbUTF8++] = UTF8_1ST_OF_3 | (wcapSrc[i] >> 12);
            if(iNbUTF8 > iDestLen) return DEST_TOO_SMALL;
            
            capDest[iNbUTF8++] = UTF8_TRAIL        | ((wcapSrc[i] >> 6) & 0x3F);
            if(iNbUTF8 > iDestLen) return DEST_TOO_SMALL;
            
            capDest[iNbUTF8++] = UTF8_TRAIL        | (wcapSrc[i] & 0x3F);
            if(iNbUTF8 > iDestLen) return DEST_TOO_SMALL;
        }
    }        
    return iNbUTF8;      
}

/**
 * Convert from UTF8 to unicode
 * Return the number of character, DEST_TOO_SMALL if the destination is too small,
 * or UTF8_BAD_STRING if the UTF8 String is invalid
 * The iDestLen should be equal to iSrcLen
 *
 * capSrc    ->    Pointer to the string to convert
 * iSrcLen   ->    Number of byte in capSrc
 * wcapDest  ->    Pointer to an allocated memory area for the converted string
 * iDestLen  ->    Size of the allocated memory area
 */
unsigned int utf8ToUnicode(const char * capSrc,unsigned int iSrcLen,wchar * wcapDest,unsigned int iDestLen){
    if(iDestLen == 0) return DEST_TOO_SMALL;
    unsigned int iNbUnicode = 0;
    unsigned int i;
    
    for(i = 0 ; i<iSrcLen ; ++i){
        
        // Found 3 bits sequence
        if((unsigned char)capSrc[i] >= UTF8_1ST_OF_3){
            if(i+2 >= iSrcLen) return UTF8_BAD_STRING;
            
            // First 8 bits
            wcapDest[iNbUnicode  ]  = ((capSrc[  i] << 4)               ) <<8;
            wcapDest[iNbUnicode  ] |= ((capSrc[++i] >> 2) & 0xf         ) <<8;
            
            // Last 8 bits
            wcapDest[iNbUnicode  ] |= (capSrc[  i] & 0x3) << 6;
            wcapDest[iNbUnicode++] |=  capSrc[++i] & 0x3F;
            
            if(iNbUnicode > iDestLen) return DEST_TOO_SMALL;
        }else
        
        // Found 2 bits sequence
        if((unsigned char)capSrc[i] >= UTF8_1ST_OF_2){
            if(i+1 >= iSrcLen) return UTF8_BAD_STRING;
            // First 8 bits
            wcapDest[iNbUnicode  ]   =  ((capSrc[  i] >> 2 ) & 0x7      ) <<8;
            
            // Last 8 bits
            wcapDest[iNbUnicode  ]  |= (capSrc[  i] & 0x3) << 6;
            wcapDest[iNbUnicode++]  |=  capSrc[++i] & 0x3F;
            
            if(iNbUnicode > iDestLen) return DEST_TOO_SMALL;
        }else
        
        // Found 1 bits sequence (ASCII)
        /* if((unsigned char)capSrc[i] >= UTF8_1ST_OF_1) */{
            wcapDest[iNbUnicode++] = capSrc[i];
            if(iNbUnicode > iDestLen) return DEST_TOO_SMALL;
        }
    }        
    return iNbUnicode;      
}

/**
 * Convert from Unicode to ISO 8859-1
 * Return iSrcLen, DEST_TOO_SMALL if the destination is too small, or
 * INCOMPATIBLE_UNICODE if it's impossible to convert from unicode to ios8835
 * The iDestLen should be equal to iSrcLen
 *
 * wcapSrc   ->    Pointer to the string to convert
 * iSrcLen   ->    Number of character in capSrc
 * capDest   ->    Pointer to an allocated memory area for the converted string
 * iDestLen  ->    Size of the allocated memory area
 */
unsigned int unicodeToIso8859(const wchar * wcapSrc,unsigned int iSrcLen,char * capDest,unsigned int iDestLen){
    if(iDestLen < iSrcLen) return DEST_TOO_SMALL;
    unsigned int i,ret = iSrcLen;
    
    for(i = 0 ; i<iSrcLen ; ++i){
        if(wcapSrc[i] >> 8 > 0)
         {
         /*ret = INCOMPATIBLE_UNICODE; fprintf(stderr,"INCOMPATIBLE_UNICODE: [%c] (i=%d,code=%d) from [%s]\n",(char)wcapSrc[i],i,(unsigned char)wcapSrc[i],(char*)wcapSrc); exit(0);*/
         fprintf(stderr,"INCOMPATIBLE_UNICODE: [%c] (i=%d,code=%d) from [%s]\n",(char)wcapSrc[i],i,(unsigned char)wcapSrc[i],(char*)wcapSrc);
         capDest[i]=' ';
         }
        else capDest[i] = wcapSrc[i];
    }    
    return ret;
}

/**
 * Convert from  ISO 8859-1 to Extended ascii
 * Return iSrcLen, DEST_TOO_SMALL if the destination is too small, or
 * INCOMPATIBLE_ISO8859 if it's impossible to convert from ios8835 to eascii
 * The iDestLen should be equal to iSrcLen
 *
 * capSrc    ->    Pointer to the string to convert
 * iSrcLen   ->    Number of character in capSrc
 * capDest   ->    Pointer to an allocated memory area for the converted string
 * iDestLen  ->    Size of the allocated memory area
 */
unsigned int iso8859ToEascii(const char * capSrc,unsigned int iSrcLen,char * capDest,unsigned int iDestLen){
    if(iDestLen < iSrcLen) return DEST_TOO_SMALL;
    unsigned int i,ret = iSrcLen;
    
    for(i = 0 ; i<iSrcLen ; ++i){
        switch((unsigned char)capSrc[i]){
            case 0xA1: capDest[i] = 0xAD; break;
            case 0xA2: capDest[i] = 0xBD; break;
            case 0xA3: capDest[i] = 0x9C; break;
            case 0xA4: capDest[i] = 0xCF; break;
            case 0xA5: capDest[i] = 0xBE; break;
            case 0xA6: capDest[i] = 0xDD; break;
            case 0xA7: capDest[i] = 0xF5; break;
            case 0xA8: capDest[i] = 0xF9; break;
            case 0xA9: capDest[i] = 0xB8; break;
            case 0xAA: capDest[i] = 0xA6; break;
            case 0xAB: capDest[i] = 0xAE; break;
            case 0xAC: capDest[i] = 0xAA; break;
            case 0xAD: capDest[i] = 0xF0; break;
            case 0xAE: capDest[i] = 0xA9; break;
            case 0xAF: capDest[i] = 0xEE; break;
            case 0xB0: capDest[i] = 0xF8; break;
            case 0xB1: capDest[i] = 0xF1; break;
            case 0xB2: capDest[i] = 0xFD; break;
            case 0xB3: capDest[i] = 0xFC; break;
            case 0xB4: capDest[i] = 0xEF; break;
            case 0xB5: capDest[i] = 0xE6; break;
            case 0xB6: capDest[i] = 0xF4; break;
            case 0xB7: capDest[i] = 0xFA; break;
            case 0xB8: capDest[i] = 0xF7; break;
            case 0xB9: capDest[i] = 0xFB; break;
            case 0xBA: capDest[i] = 0xA7; break;
            case 0xBB: capDest[i] = 0xAF; break;
            case 0xBC: capDest[i] = 0xAC; break;
            case 0xBD: capDest[i] = 0xAB; break;
            case 0xBE: capDest[i] = 0xF3; break;
            case 0xBF: capDest[i] = 0xA8; break;
            case 0xC0: capDest[i] = 0xB7; break;
            case 0xC1: capDest[i] = 0xB5; break;
            case 0xC2: capDest[i] = 0xB6; break;
            case 0xC3: capDest[i] = 0xC7; break;
            case 0xC4: capDest[i] = 0x8E; break;
            case 0xC5: capDest[i] = 0x8F; break;
            case 0xC6: capDest[i] = 0x92; break;
            case 0xC7: capDest[i] = 0x80; break;
            case 0xC8: capDest[i] = 0xD4; break;
            case 0xC9: capDest[i] = 0x90; break;
            case 0xCA: capDest[i] = 0xD2; break;
            case 0xCB: capDest[i] = 0xD3; break;
            case 0xCC: capDest[i] = 0xDE; break;
            case 0xCD: capDest[i] = 0xD6; break;
            case 0xCE: capDest[i] = 0xD7; break;
            case 0xCF: capDest[i] = 0xD8; break;
            case 0xD0: capDest[i] = 0xD1; break;
            case 0xD1: capDest[i] = 0xA5; break;
            case 0xD2: capDest[i] = 0xE3; break;
            case 0xD3: capDest[i] = 0xE0; break;
            case 0xD4: capDest[i] = 0xE2; break;
            case 0xD5: capDest[i] = 0xE5; break;
            case 0xD6: capDest[i] = 0x99; break;
            case 0xD7: capDest[i] = 0x9E; break;
            case 0xD8: capDest[i] = 0x9D; break;
            case 0xD9: capDest[i] = 0xEB; break;
            case 0xDA: capDest[i] = 0xE9; break;
            case 0xDB: capDest[i] = 0xEA; break;
            case 0xDC: capDest[i] = 0x9A; break;
            case 0xDD: capDest[i] = 0xED; break;
            case 0xDE: capDest[i] = 0xE7; break;
            case 0xDF: capDest[i] = 0xE1; break;
            case 0xE0: capDest[i] = 0x85; break;
            case 0xE1: capDest[i] = 0xA0; break;
            case 0xE2: capDest[i] = 0x83; break;
            case 0xE3: capDest[i] = 0xC6; break;
            case 0xE4: capDest[i] = 0x84; break;
            case 0xE5: capDest[i] = 0x86; break;
            case 0xE6: capDest[i] = 0x91; break;
            case 0xE7: capDest[i] = 0x87; break;
            case 0xE8: capDest[i] = 0x8A; break;
            case 0xE9: capDest[i] = 0x82; break;
            case 0xEA: capDest[i] = 0x88; break;
            case 0xEB: capDest[i] = 0x89; break;
            case 0xEC: capDest[i] = 0x8D; break;
            case 0xED: capDest[i] = 0xA1; break;
            case 0xEE: capDest[i] = 0x8C; break;
            case 0xEF: capDest[i] = 0x8B; break;
            case 0xF0: capDest[i] = 0xD0; break;
            case 0xF1: capDest[i] = 0xA4; break;
            case 0xF2: capDest[i] = 0x95; break;
            case 0xF3: capDest[i] = 0xA2; break;
            case 0xF4: capDest[i] = 0x93; break;
            case 0xF5: capDest[i] = 0xE4; break;
            case 0xF6: capDest[i] = 0x94; break;
            case 0xF7: capDest[i] = 0xF6; break;
            case 0xF8: capDest[i] = 0x9B; break;
            case 0xF9: capDest[i] = 0x97; break;
            case 0xFA: capDest[i] = 0xA3; break;
            case 0xFB: capDest[i] = 0x96; break;
            case 0xFC: capDest[i] = 0x81; break;
            case 0xFD: capDest[i] = 0xEC; break;
            case 0xFE: capDest[i] = 0xE8; break;
            case 0xFF: capDest[i] = 0x98; break;
            
            default:
                if((unsigned char)capSrc[i] > ASCII) ret = INCOMPATIBLE_ISO8859;
                capDest[i] = capSrc[i];
        }
    }
    return ret;
}
 
