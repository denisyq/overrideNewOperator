#ifndef _TRACE_H_
#define _TRACE_H_

#include <map>
#include <malloc.h>
#ifndef NDEBUG

void *operator new(size_t size,const char *file,long line);
void operator delete(void *p);

void *operator new[](size_t size,const char *file, long line);
void operator delete[](void *p);

class Trace{
    private:
        class Entry{
            public:
                Entry(const char *file=0,long line=0):file_(file),line_(line){}
                const char *File() const { return file_;}
                long Line() const { return line_;}
            private:
                const char *file_;
                long line_;
        };
        std::map<void *,Entry> mapEntry_;
    public:
        Trace();
        ~Trace();
        static bool ready;

        void add(void *p, const char *file, long line);
        void remove(void *p);
        void dump();

};

#endif
#endif
