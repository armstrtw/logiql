#pragma once
/* Copyright (c) 2015 Whit Armstrong
   The below class is a modification of the partial_date
   class implemented in boost.
 */
/* Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 */

#include <stdexcept>
#include <sstream>
#include <boost/throw_exception.hpp>
#include <boost/date_time/date.hpp>
#include <boost/date_time/compiler_config.hpp>

namespace boost {
  namespace date_time {

    // Same operation as the orginal class (per below)
    // with the following modifications:
    // Saturday dates are rolled back to Friday
    // Sunday dates are rolled forward to Monday

    //! Generates a date by applying the year to the given month and day.
    /*!
      Example usage:
      @code
      partial_date pd(1, Jan);
      partial_date pd2(70);
      date d = pd.get_date(2002); //2002-Jan-01
      date d2 = pd2.get_date(2002); //2002-Mar-10
      @endcode
      \ingroup date_alg
    */
    template<class date_type>
    class observed_partial_date : public year_based_generator<date_type>
    {
    public:
      typedef typename date_type::calendar_type calendar_type;
      typedef typename calendar_type::day_type         day_type;
      typedef typename calendar_type::month_type       month_type;
      typedef typename calendar_type::year_type        year_type;
      typedef typename date_type::duration_type        duration_type;
      typedef typename duration_type::duration_rep     duration_rep;
      observed_partial_date(day_type d, month_type m) :
        day_(d),
        month_(m)
      {}
      //! Partial date created from number of days into year. Range 1-366
      /*! Allowable values range from 1 to 366. 1=Jan1, 366=Dec31. If argument
       * exceeds range, observed_partial_date will be created with closest in-range value.
       * 60 will always be Feb29, if get_date() is called with a non-leap year
       * an exception will be thrown */
      observed_partial_date(duration_rep days) :
      day_(1), // default values
      month_(1)
      {
        date_type d1(2000,1,1);
        if(days > 1) {
          if(days > 366) // prevents wrapping
            {
              days = 366;
            }
          days = days - 1;
          duration_type dd(days);
          d1 = d1 + dd;
        }
        day_ = d1.day();
        month_ = d1.month();
      }
      //! Return a concrete date when provided with a year specific year.
      /*! Will throw an 'invalid_argument' exception if a observed_partial_date object,
       * instantiated with Feb-29, has get_date called with a non-leap year.
       * Example:
       * @code
       * observed_partial_date pd(29, Feb);
       * pd.get_date(2003); // throws invalid_argument exception
       * pg.get_date(2000); // returns 2000-2-29
       * @endcode
       */
      date_type get_date(year_type y) const
      {
        if((day_ == 29) && (month_ == 2) && !(calendar_type::is_leap_year(y))) {
          std::ostringstream ss;
          ss << "No Feb 29th in given year of " << y << ".";
          boost::throw_exception(std::invalid_argument(ss.str()));
        }
        date_type ans(y, month_, day_);

        // Saturday rolls back to Friday
        if(ans.day_of_week() == Saturday) { ans -= duration_type(1); }

        // Sunday rolls forward to Monday
        if(ans.day_of_week() == Sunday) { ans += duration_type(1); }

        return ans;
      }
      date_type operator()(year_type y) const
      {
        return get_date(y);
        //return date_type(y, month_, day_);
      }
      bool operator==(const observed_partial_date& rhs) const
      {
        return (month_ == rhs.month_) && (day_ == rhs.day_);
      }
      bool operator<(const observed_partial_date& rhs) const
      {
        if (month_ < rhs.month_) return true;
        if (month_ > rhs.month_) return false;
        //months are equal
        return (day_ < rhs.day_);
      }

      // added for streaming purposes
      month_type month() const
      {
        return month_;
      }
      day_type day() const
      {
        return day_;
      }

      //! Returns string suitable for use in POSIX time zone string
      /*! Returns string formatted with up to 3 digits:
       * Jan-01 == "0"
       * Feb-29 == "58"
       * Dec-31 == "365" */
      virtual std::string to_string() const
      {
        std::ostringstream ss;
        date_type d(2004, month_, day_);
        unsigned short c = d.day_of_year();
        c--; // numbered 0-365 while day_of_year is 1 based...
        ss << c;
        return ss.str();
      }
    private:
      day_type day_;
      month_type month_;
    };

  } // namespace date_time
} // namespace boost
