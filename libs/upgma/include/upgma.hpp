#include "../../utils/bwokFeedback.hpp"
#include "../../utils/bwokMath.hpp"
#include "../../utils/bwokTypedMatrix.hpp"
#include "../../utils/bwokPartialTypedMatrix.hpp"
#include "../../utils/bwokCString.hpp"
class PhylogeneticTree {
    private:    bool m_mat_on_heap, m_clus_on_heap;
    public:     char *m_sqs; 
                unsigned int m_n, m_k, m_wd;
                bwokPMat<float> *m_mat; float *m_cls;
    public:
        PhylogeneticTree( unsigned int n , unsigned int k , char *sequences , bwokPMat<float> *distance_matrix=nullptr , float *cluster_map=nullptr ) : 
            m_mat_on_heap{(distance_matrix==nullptr)?true:false} ,
            m_clus_on_heap{(cluster_map==nullptr)?true:false} , 
            m_n{n} , m_k{k} , m_wd{k+(k-1)} , 
            m_sqs{sequences} , 
            m_mat{(distance_matrix==nullptr)?new bwokPMat<float>{k+(k-1)}:distance_matrix} , 
            m_cls{(distance_matrix==nullptr)?new float[4*(k-1)]:cluster_map} { 
                compose(); 
        }
        ~PhylogeneticTree(){
            if(m_mat_on_heap) delete m_mat;
            if(m_clus_on_heap) delete[] m_cls;
        };
        inline unsigned int distance_matrix_usage(){ return bwok_math::nsum(m_wd)*sizeof(unsigned int); }
        inline unsigned int cluster_map_usage(){ return (5*(m_k-1))*sizeof(float); }
        inline unsigned int total_space_usage(){ return (bwok_cstr::glen(m_sqs)*m_k) + ((m_wd*m_wd)*sizeof(unsigned int)) + ((4*(m_k-1))*sizeof(float)); }
    private:
        void compose();
        void build_matrix();
        void cluster();
};