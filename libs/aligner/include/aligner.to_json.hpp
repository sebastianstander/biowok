#include <stdio.h>
#include <aligner.hpp>

void from_JSON( Aligner& DAT ) {

}
void to_JSON( Aligner& DAT ) {
    FILE* resulting_json = fopen("aligner_results.json","w");
    fprintf(resulting_json,"{\n\t\"alignment_type\":\"%s\",",(!!DAT.m_is_local)?"Smith-Waterman":"Needleman-Wunsch");
    fprintf(resulting_json,"\n\t\"sequence_A\":\"%s\",",DAT.m_sqA);
    fprintf(resulting_json,"\n\t\"sequence_B\":\"%s\",",DAT.m_sqB);
    fprintf(resulting_json,"\n\t\"scoremodel\":{");
    fprintf(resulting_json,"\n\t\t\"match\":\"%s\",",DAT.m_SM.match);
    fprintf(resulting_json,"\n\t\t\"mismatch\":\"%s\",",DAT.m_SM.mismatch);
    fprintf(resulting_json,"\n\t\t\"gap\":\"%s\"\n\t},",DAT.m_SM.gap);
    fprintf(resulting_json,"\n\t\"distance_matrix\":\"%s\"[\n\t\t");
    for( int i = 0 ; i < DAT.m_n*DAT.m_m-1  ; i++ )
        fprintf(resulting_json,"%d, ",DAT.m_mat->gti(i));
    fprintf(resulting_json,"%d",DAT.m_mat->gti(DAT.m_n*DAT.m_m-1));
    fprintf(resulting_json,"\n\t\"distance_matrix_width\":%d,",DAT.m_n);
    fprintf(resulting_json,"\n\t\"optimal_alignment_string\":%s",DAT.m_AL->m_str);
    fprintf(resulting_json,"}");
    fclose(resulting_json);
}
int main( int argc , char* argv[] ){

    Aligner OUT_DAT{};
    from_JSON( argv[1] , Aligner& OUT_DAT );
    char sqA[n] = ; 

    char sqB[m] = ; 


    fclose(input_json);
    FILE* input_json = fopen(filepath,"r");
    Aligner OUT_DAT { argv[1] , argv[2] , true };
    to_JSON( OUT_DAT );
}
