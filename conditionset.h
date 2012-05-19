/**
 * @file conditionset.h
 * @author A M
 * @version 1.0.0
 * @brief conditionset.h is the header of libcondset
 */

/**
 * @mainpage Libcondset: Predicate and data sets
 * @par Description
 *  Libcondset is used to manipulate sets of predicates and data.
 *  Homepage: https://sourceforge.net/projects/libcondsetlib/
 */

#ifndef FLAGSET_H
#define	FLAGSET_H
#include <arpa/inet.h>
#include <stdexcept>
#include <cstring>
#include <iostream>
using namespace std;

/**
 * @brief An enumeration of integer predicates.
 * The CondPredicate enum is used to specify a integer predicate (equals, not equals, less then, etc.).
 * The predicate Unspec is used either when the predicate is unnecessary (being the right operand of CoditionSet::compare), or when the other sets data can be anything.
 */
enum CondPredicate
{ 
    Equals=0,
    NotEquals,
    LessThen,
    GreaterThen,
    LessThenEqual,
    GreaterThenEqual,
    Unspec,
};
/**
 * @brief Represents a condition.
 * Struct Condition is used to represent a condition that can be matched or not matched. If Unspec is specified as the predicate, this is essentially a glorified uint16_t.
 */
struct Condition
{
    CondPredicate pred; /**< @c pred is the predicate to be used*/
    uint16_t data; /**< The data for the predicate to use as its left hand side*/
};
/**
 * @brief ConditionSet represents a set of conditions that can all be matched by another ConditionSet or not.
 * Class ConditionSet is the main portion of libcondset. It is used to represent an array of Conditions that can be compared to another ConditionSet.
 * 
 * Example:
 * @code
 * Condition cs[]={{Equals, 56}, {LessThen, 90}};
 * Condition cs2[]={{Unspec, 56}, {Unspec, 78}};
 * Condition cs3[]={{Unspec, 78}, {Unspec, 890}};
 * ConditionSet c(cs, 2);
 * ConditionSet c2(cs2, 2);
 * ConditionSet c3(cs3, 2);
 * c.compare(c2) //true
 * c.compare(c3) //false
 * @endcode
 */
class ConditionSet {
public:
    /**
     * @brief Constructs a ConditionSet.
     * This constructor takes an array of Condition objects and the length of the array.
     * @param flags: an array of struct Conditions
     * @param len: the number of elements in @a flags
     */
    ConditionSet(const Condition* flags, const uint16_t len);
    /**
     * @brief Constructs a ConditionSet from a binary string.
     * This is used to construct a ConditionSet from a binary string that was initially acquired with ConditionSet::getBinary()
     * @warning NEVER use this function with anything but a string from getBinary(). A segmentation fault is an almost definite result.
     * @param binFlagset: The binary string to use
     */
    explicit ConditionSet(const char* binFlagset);
    /**
     * @brief Get a portable binary representation of a ConditionSet.
     * Use this function to get the binary representation of an object. Can be sent verbatim over the wire.
     * @warning The char string passed into this function @b MUST be of the length returned by ConditionSet::getBinSize(). Otherwise segmentation faults are almost definite.
     * @param dest: A pointer to an array of chars on length getBinSize()
     */
    void getBinary(char* dest) const;
    /**
     * @brief Get the number of bytes necessary for the storage of the binary representation of the flagset.
     * This is the number of byte necessary to store THIS conditions set's binary representation.
     * @warning Call this on EACH condition set that you intend to persist.
     * @return The number of bytes
     */
    int getBinSize() const;
    /**
     * @brief This function uses the ConditionSet's data and predicates and compares it to another ConditionSet.
     * This function is the main function of class @c ConditionSet. It allows you to compare one @c ConditionSet 's data to another's using the first's predicates.
     * This function loops through the @c Condition s of @c this. For each condition, it finds the corresponding element of the @c Condition array of @a other.
     * It then uses @c this 's data as the right hand side, and @a other 's data as the left hand side of the operator specified in @c this 's @c Condition. If @c false,
     * it returns @c false immediately. If it returns @c true, it continues to the next @c Condition, repeating the same process.
     * 
     * The use of the @c Unspec member of @c CondPredicate is useful here. If a ConditionSet is to be used only as the right side of a comparison, there is no reason
     * to have an unused predicate.
     * 
     * Throws a @c runtime_error if @a other 's length does not equal @c this 's length.
     * @param other: The @c ConditionSet to compare to
     * @return Whether @a other 's data fits the predicates specified by @c this.
     * Example:
     * @code
     * Condition cs[]={{Equals, 56}, {LessThen, 90}};
     * Condition cs2[]={{Unspec, 56}, {Unspec, 78}};
     * Condition cs3[]={{Unspec, 78}, {Unspec, 890}};
     * ConditionSet c(cs, 2);
     * ConditionSet c2(cs2, 2);
     * ConditionSet c3(cs3, 2);
     * c.compare(c2) //true
     * c.compare(c3) //false
     * @endcode
     */
    bool compare(const ConditionSet other) const;
    ~ConditionSet();
protected:
    Condition* flags_;
    uint16_t len_;
private:
    bool dymem;
};
#endif	/* FLAGSET_H */

