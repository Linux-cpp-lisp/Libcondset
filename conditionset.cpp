/* 
 * File:   Flagset.cpp
 * Author: a
 * 
 * Created on March 24, 2012, 8:40 AM
 */

#include "conditionset.h"

ConditionSet::ConditionSet(const Condition* flags, const uint16_t len)
{
    flags_=const_cast<Condition*>(flags);
    len_=len;
    dymem=false;
}
ConditionSet::ConditionSet(const char* binFlagset)
{
    len_=ntohs(*reinterpret_cast<const uint16_t*>(binFlagset));
    dymem=true;
    flags_=new Condition[len_];
    int i=0;
    for(const char* p=binFlagset+2; i < len_; p+=3) //p != binFlagset+(len_*3)+2
    {
        flags_[i].pred=(CondPredicate)*p;
        flags_[i].data=ntohs(*reinterpret_cast<const uint16_t*>(p+1));
        i++;
    }
}
bool ConditionSet::compare(ConditionSet other) const
{
    if(other.len_ != len_)
        throw runtime_error("The two flagsets must be of the same length.");
    for(int i=0; i<len_; i++)
    {
        switch(flags_[i].pred)
        {
            case Equals:
                if(!(flags_[i].data == other.flags_[i].data))
                {
                    //cerr<<"== false\n";
                    return false;
                }
                break;
            case NotEquals:
                if(!(flags_[i].data != other.flags_[i].data))
                {
                    //cerr<<"!= false\n";
                    return false;
                }
                break;
            case GreaterThen:
                if(!(other.flags_[i].data > flags_[i].data))
                {
                    //cerr<<"> false\n";
                    return false;
                }
                break;
            case LessThen:
                if(!(other.flags_[i].data < flags_[i].data))
                {
                    //cerr<<"< false\n";
                    return false;
                }
                break;
            case GreaterThenEqual:
                if(!(other.flags_[i].data >= flags_[i].data))
                {
                    //cerr<<">= false\n";
                    return false;
                }
                break;
            case LessThenEqual:
                if(!(other.flags_[i].data <= flags_[i].data))
                {
                    //cerr<<"<= false\n";
                    return false;
                }
                break;
            case Unspec:
                //cerr<<"Unspec\n";
                break;
        }
    }
    return true;
}
void ConditionSet::getBinary(char* dest) const
{
    uint16_t temp=htons(len_);
    memcpy(dest, reinterpret_cast<char*>(&temp), 2);
    int i=0;
    
    for(char* p=dest+2; p<dest+len_*3; p+=3)
    {
        temp=htons(flags_[i].data);
        *p=flags_[i].pred;
        memcpy(p+1, &temp, 2);
        i++;
    }
}
int ConditionSet::getBinSize() const
{
    return (len_*3)+2;
}

ConditionSet::~ConditionSet()
{
    if(dymem)
        delete [] flags_;
}