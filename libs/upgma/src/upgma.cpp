#include "../include/upgma.hpp"
void PhylogeneticTree::compose() {                                          fdbk("\tAssigning m_UPGMA data:\n\t\tm_sqs : \"%s\"\n\t\tm_n : %d\n\t\tm_wd : %d\n\t\tm_k : %d\n",m_sqs,m_n,m_wd,m_k);                                                                          
    build_matrix();                                                         fdbk("\t\tm_mat :\n"); m_mat->display();
    cluster();                                                              fdbk("\t\tm_mat :\n"); m_mat->display();                                                           
}
void PhylogeneticTree::build_matrix(){                                      fdbk("\tBuilding distance matrix...\n");
    float cur;                                           
    for( int x=0 ; x<m_wd ; x++ ){
        for( int y=x ; y<m_wd ; y++ ){                                         
            cur = ( ((x>=m_k)||(y>=m_k))*(-1.0) );                  
            if( !cur && (x!=y) ){                                           fdbk("\t\tFor m[S%d,S%d]...\n\t\t\t",x,y);
                for( int i=0; i<m_n ; i++ ){                                   
                    cur = cur + float(m_sqs[(m_n*x)+i]!=m_sqs[(m_n*y)+i]);  fdbk("%d=(\'%c\'&\'%c\'),",i,m_sqs[(m_n*x)+i],m_sqs[(m_n*y)+i]);                                                                 
                }                                                           fdbk("\n");    
            }                                                                                                                               
            m_mat->st(x,y,cur);                                             fdbk("\t\t\tmatrix accessor formula ( m[(%d*%d)-%d+%d](%d) = %f ; )...\n",x,m_wd,bwok_math::nsum(x),y,(x*m_wd)-bwok_math::nsum(x)+y,cur);                                                                            
        }
    }                                                                       fdbk("\tdistance matrix built...\n");
}
void PhylogeneticTree::cluster(){                                           fdbk("\tclustering sequences...\n");
    bool is_smallest;
    int km = m_k, minx, miny;
    float smallest_distance;
    for( int clus = 0 ; clus<(m_k-1)*4 ; clus+=4 ){                         fdbk("\t\tcreating pair for cluster %d (at i%d&i%d) of %d...\n",km,clus,clus+1,(m_k-1)*2);  
                                                                            fdbk("\n\t\t1. Finding the smallest value & it's indices...\n");
        smallest_distance = m_n+1;                                             
        for( int x=0 ; x<km ; x++ ){
            for( int y=x+1 ; y<km ; y++ ){                                      
                is_smallest = ((m_mat->gt(x,y)<smallest_distance)) && (m_mat->gt(x,y)>0.0);
                smallest_distance = is_smallest?m_mat->gt(x,y):smallest_distance;
                minx = is_smallest?x:minx;                                      
                miny = is_smallest?y:miny;                               
            }
        }                                                                   fdbk("\t\t\tsmallest found = (%f) at m[%d,%d]...\n",smallest_distance,minx,miny);

        fdbk("\n\t\t2. Calculating values for the new/current cluster %d using S%d and S%d...\n",km,minx,miny);    
        for( int x=0 ; x<km ; x++ ){                                        fdbk("\t\t\testablishing m[%d,%d] as ( (m[%d,%d]<%d> + m[%d,%d]<%d> ) ==> %d / 2  =  %f )...\n",
                                                                                    x,
                                                                                    km,
                                                                                    (minx<x)?minx:x,
                                                                                    (minx<x)?x:minx,
                                                                                    int((minx<x)?m_mat->gt(minx,x):m_mat->gt(x,minx)),
                                                                                    (miny<x)?miny:x,
                                                                                    (miny<x)?x:miny,
                                                                                    int((miny<x)?m_mat->gt(miny,x):m_mat->gt(x,miny)),
                                                                                    int(((minx<x)?m_mat->gt(minx,x):m_mat->gt(x,minx))+((miny<x)?m_mat->gt(miny,x):m_mat->gt(x,miny)) ),
                                                                                    ((((minx<x)?m_mat->gt(minx,x):m_mat->gt(x,minx))+((miny<x)?m_mat->gt(miny,x):m_mat->gt(x,miny)))/2) 
                                                                                    );
            m_mat->st(x,km,((((minx<x)?m_mat->gt(minx,x):m_mat->gt(x,minx))+((miny<x)?m_mat->gt(miny,x):m_mat->gt(x,miny)))/2));
        } 
        m_cls[clus] = float(km);
        km++;                                                                 fdbk("\n\t\t\tm_mat's new column/cluster(%d) :\n",clus); m_mat->display();
        
        fdbk("\n\t\t3. Negating S%d & S%d :\n\t\t\tFor S%d: ",miny,minx,miny);
        for( int x=0 ; x<km ; x++ ){                                            
            fdbk("-m[%d,%d]",(miny<x)?miny:x,(miny<x)?x:miny);
            m_mat->st( (miny<x)?miny:x, (miny<x)?x:miny, (miny<x)?(-bwok_math::abs(m_mat->gt(miny,x))):(-bwok_math::abs(m_mat->gt(x,miny))));      
        }

        fdbk("\n\t\t\tFor S%d: ",minx);
        for( int y=0 ; y<km ; y++ ){                                            
            fdbk("-m[%d,%d]",(minx<y)?minx:y,(minx<y)?y:minx);
            m_mat->st((minx<y)?minx:y,(minx<y)?y:minx,(minx<y)?(-bwok_math::abs(m_mat->gt(minx,y))):(-bwok_math::abs(m_mat->gt(y,minx))));
        } fdbk("\n\n\t\t\tm_mat's new column/cluster after negation(%d) :\n",clus); m_mat->display();
        
        fdbk("\n\t\t4. Recording Cluster in int array as [%d]=%d & [%d]=%d :\n  ",clus,minx,(clus+1),miny);     
        m_cls[clus+1] = bwok_math::abs(m_mat->gt(minx,miny));
        m_cls[clus+2] = float(minx);
        m_cls[clus+3] = float(miny);                            fdbk("\t\t\tnew cluster created (%f : %f (%f,%f)...\n",m_cls[clus],m_cls[clus+1],m_cls[clus+2],m_cls[clus+3]);
                                                                fdbk("\n\n\tfinalized clusterings:...\n"); print_mat(m_cls,1,4*(m_k-1)); fdbk("\n");
    }                                                           fdbk("\tcompleted clustering sequences...\n");
    return;                                                               
}
