#include <iostream>
#include "trace.h"

#ifndef NDEBUG

bool Trace::ready = false;

Trace::Trace(){
    ready = true;
}
Trace::~Trace(){
    ready =  false;
    dump();
}

void Trace::add(void *p,const char *file, long line){
    mapEntry_[p] = Entry(file,line);
}

void Trace::remove(void *p){
    std::map<void *,Entry>::iterator it;
    it = mapEntry_.find(p);
    if(it != mapEntry_.end())
        mapEntry_.erase(it);
}

void Trace::dump(){
    if(mapEntry_.size() > 0){
        std::cout<<"***memory leak:"<<std::endl;
        std::map<void*,Entry>::iterator it;
        for(it=mapEntry_.begin();it!=mapEntry_.end();it++){
            const char *file = it->second.File();
            long line = it->second.Line();
            int addr = reinterpret_cast<int>(it->first);
            std::cout<<"0x"<<std::hex<<addr<<":"<<file<<",line"<<std::dec<<line<<std::endl;
        }
        std::cout<<std::endl;
    }
}

Trace newTrace;
void *operator new(size_t size, const char* file, long line){
    void* p = malloc(size);
    if(Trace::ready)
        newTrace.add(p,file,line);
    return p;
}

void operator delete(void* p){
    if(Trace::ready)
        newTrace.remove(p);
    free(p);
}
void *operator new[](size_t size, const char* file, long line){
    void *p = malloc(size);
    if(Trace::ready)
        newTrace.add(p,file,line);
    return p;
}
void operator delete[](void *p){
    if(Trace::ready)
        newTrace.remove(p);
    free(p);
}
#endif
