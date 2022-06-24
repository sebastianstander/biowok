#include <iostream>
int main(int argc,char* arvv[]){
    int bigarray[9000];
    for( int i = 0 ; i<9000 ; i++) bigarray[i] = i ;
    std::cout<<"\nRLIMIT_CORE == "<<RLIMIT_CORE<<std::endl;
    std::cout<<"RLIMIT_CPU == "<<float(RLIMIT_CPU)<<std::endl;
    std::cout<<"RLIMIT_DATA == "<<RLIMIT_DATA<<std::endl;
    std::cout<<"RLIMIT_FSIZE == "<<RLIMIT_FSIZE<<std::endl;
    std::cout<<"RLIMIT_MEMLOCK == "<<RLIMIT_MEMLOCK<<std::endl;
    std::cout<<"RLIMIT_NOFILE == "<<RLIMIT_NOFILE<<std::endl;
    std::cout<<"RLIMIT_NPROC == "<<RLIMIT_NPROC<<std::endl;
    std::cout<<"RLIMIT_RSS == "<<RLIMIT_RSS<<std::endl;
    std::cout<<"RLIMIT_STACK == "<<RLIMIT_STACK<<std::endl;
    for( int i = 0 ; i<9000 ; i++) std::cout<<bigarray[i] ;
    std::cout<<"\nRLIMIT_CORE == "<<RLIMIT_CORE<<std::endl;
    std::cout<<"RLIMIT_CPU == "<<float(RLIMIT_CPU)<<std::endl;
    std::cout<<"RLIMIT_DATA == "<<RLIMIT_DATA<<std::endl;
    std::cout<<"RLIMIT_FSIZE == "<<RLIMIT_FSIZE<<std::endl;
    std::cout<<"RLIMIT_MEMLOCK == "<<RLIMIT_MEMLOCK<<std::endl;
    std::cout<<"RLIMIT_NOFILE == "<<RLIMIT_NOFILE<<std::endl;
    std::cout<<"RLIMIT_NPROC == "<<RLIMIT_NPROC<<std::endl;
    std::cout<<"RLIMIT_RSS == "<<RLIMIT_RSS<<std::endl;
    std::cout<<"RLIMIT_STACK == "<<RLIMIT_STACK<<std::endl;
    int limit;
    getrlimit(RLIMIT_STACK,&limit)
    std::cout<<"getrlimit() == "<<limit<<std::endl;
}
/*
Mac OSX 16.?
RLIMIT_CORE == 4        Max size (0b) core file that may be created 
RLIMIT_CPU == 0         Max usable CPU time (sec) for by each process
RLIMIT_DATA == 2        Max size (0b) of the process data segment
                        Extention limit for sbrk(2) syscall
RLIMIT_FSIZE == 1       Max size (0b) file that may be created
RLIMIT_MEMLOCK == 6     Max size (0b) which a process may lock using mlock(2)
RLIMIT_NOFILE == 8      Max number of open files for this process
RLIMIT_NPROC == 7       Max number of simultaneous processes for this user id
RLIMIT_RSS == 5         Max size (0b) to which a process's resident set size may grow.
                        Imposes limit on amount of phys.mem to be given to a process.
                        If tight, sys will prefer memory from processes exceeding resident set size.           
RLIMIT_STACK == 3       Max size (0b) of the stack segment for a process.
                        This defines how far a program's stack my extend.
                        Extension is performed automatically by the system.
*/