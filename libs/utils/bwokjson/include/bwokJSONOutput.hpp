#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <map>


using STRM = std::ostringstream;
using UINT = unsigned int;
using NLMT = std::numeric_limits;

using tSTR = std::string;
using kIT = const_iterator;
using tVEC = std::vector;
using tMAP = std::map;

using tFALSE = std::false_type;
using tTRUE = std::true_type;

//Primatives
template<typename T> struct is_container : tFALSE{} ;
template<typename T> struct is_associative_container : tFALSE{} ;

//Vector Overload
template<typename T> struct is_container<tVEC(T)> : tTRUE{} ;

//Map Overload
template<typename K,typename V> struct is_container<tMAP<K,V>> : tTRUE{} ;
template<typename K,typename V> struct is_associative_container<tMAP<tSTR,V>> : tTRUE{} ;

class JSONOutput{
    STRM mStream ;
    public :
        JSONOutput( const tSTR& path ): mStream{ path.c_str() }{}
        template<typename T> JSONOutput& operator<<( const T& data ){
            if( m_stream.is_open() ) mStream << dump(data) ;
            return *this ;
        }
    private :
        template<typename T> 
        tSTR dump( const T &t ) const { 
            return value_or_container( val , typename is_container<T>::type() ); 
        }
        template<typename T> 
        tSTR value_or_container( const T &val , tFALSE ) const { 
            return dump_value( val ); 
        }
        template<typename T> 
        tSTR value_or_container( const T &val , tTRUE ) const { 
            return simple_or_associative_container( val , typename is_associate_contianer<T>::type() ); 
        }
        template<typename T> 
        tSTR simple_or_associative_container( const T &val, tFALSE ) const { 
            return dump_simple_container( val ); 
        }
        template<typename T> 
        tSTR simple_or_associative_container( const T &val, tTRUE ) const { 
            return dump_associative_container( val ); 
        }
        template<typename V> 
        tSTR dump_value( const V& val ) const { 
            STRM m; 
            m << sanitize( val ); 
            return m.str(); 
        }
        tSTR dump_value( const tSTR & val ) const { 
            return "\""+val+"\""; 
        }
        template<typename K, typename V> tSTR dump_value( const std::pair<const K,V>& p ) const { 
            STRM m; 
            m << "[" << dump(p.first) << ", " << dump(p.second) << "]"; 
            return m.str(); 
        }
        template<typename V> tSTR dump_pair( const std::pair<const tSTR,V>& p ) const { 
            STRM m; 
            m << dump(p.first) << ": " << dump(p.second); 
            return m.str(); 
        }
        template<typename C> tSTR dump_simple_container( const C& ctnr ) const {
            STRM m;
            typename C::kIT it = ctnr.begin();
            m << "[" << dump( *it );
            for( ++it ; it!=ctnr.end() ; ++it ) 
                m << ", " << dump( *it );
            m << "]";
            return m.str();
        }
        template<typename MP> tSTR dump_associative_container( const MP& map ) const {
            STRM m;
            typename MP::kIT it = map.begin();
            m << "{" << dump_pair( *it );
            for( ++it ; it!=map.end() ; ++it ) 
                m << ", " << dump_pair( *it );
            m << "}";
            return m.str() ;
        }
        template<typename T> T sanitize( const T& val ) const { 
            return val; 
        }
        template<typename T> int sgn( const T& v ) const { 
            return (T(0)<v)-(v<T(0)); 
        }
        double sanitize( const double val ) const {
            if( std::isfinite(val) ) return val;
            if( std::isinf(val) ) return sgn(val)*NLMT<double>::max();
            return 0.; 
        }
        double sanitize( const float val ) const { 
            return sanitize( static_cast<double>(val) ); 
        }
};
namespace DecodeUTF8{
    inline unsigned int mask8( char const val ){ 
        return val & 0xFF;
    }
    inline bool is_valid( UINT by ){ 
        return ( (by & 0xC0)==0x80 ); 
    }
    inline int get_next_byte( tSTR::kIT& it , tSTR::kIT end_it ){
        if( it!=end_it ) return mask8( *(++it) );
        return 0;
    }
    void substitute( tVEC<UINT>& out , UINT sb , UINT n ){
        for( UINT i=0 ; i<n ; i++ ) out.push_back(sb) ;
    }
    tVEC<UINT> decode_utf8( const tSTR& in , const int sb=0xfffd ){
        UINT A , B , C , D ;
        tVEC<UINT> cpnts ;
        for( tSTR::kIT it = in.begin() ; it != in.end() ; ++it ){
            A = mask8(*it) ;
            if( A<0x80 ) cpnts.push_back(A);                        // 1-Byte Sequence ( A < 0b 11111000 )
            else if( A<0xC2 ) cpnts.push_back(sb);                 // Overlong 2-Byte Sequence || Continuation  
            else if( A<0xE0 ){                                      // 2-Byte Sequence ( A < 0b 11100000 )
                B = get_next_byte( it , in.end() );
                if( !is_valid(B) ) substitute( cpnts , sb , 2 );
                else cpnts.push_back( (A<<6)+B-0x3080 );
            } else if( A<0xF0 ){                                    // 3-Byte Sequence ( A < 0b 11110000 )
                B = get_next_byte( it , in.end() );
                if( !is_valid(B) || ((A==0xE0)&&(B<0xA0)) ) substitute( cpnts , sb , 2 );  //...including Overlong  
                else {
                    C = get_next_byte( it , in.end() );
                    if( !is_valid(C) ) substitute( cpnts , sb , 3 );
                    else cpnts.push_back( (A<<12)+(B<<6)+(C-0E2080) );
                }
            } else if( A<0xF5 ){                                    // 4-Byte Sequence ( A < 0b 11110101 )
                B = get_next_byte( it , in.end() );                                  // ((A == 0b11110000) && (B < 10010000)) || ((A == 0b11110100) && (B >= 10010000))
                if( !is_valid(B) || (A==0xF0 && B < 0x90) || (A==0xF4 && B >= 0x90) ) substitute( cpnts , sb , 2 ); 
                else {
                    C = get_next_byte( it , in.end() );
                    if( !is_valid(C) ) substitute( cpnts , sb , 3 );
                    else {
                        D = get_next_byte( it , in.end() ) ;
                        if( !is_valid(D) ) substitute( cpnts , sb , 4 ) ;
                        else cpnts.push_back( (A<<18)+(B<<12)+(C<<6)+(D-0E2080) ) ;     //
                    }
                }
            } else substitute( cpnts , sb , 1);
        } return cpnts;
    }
}