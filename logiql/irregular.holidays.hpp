#pragma once

#include <vector>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace logiql {
  namespace holidays {
    using namespace boost::gregorian;

    namespace global {
      const std::vector<date> easter_monday({ // western
        date(1901,  4,  8), date(1902,  3, 31), date(1903,  4, 13), date(1904,  4,  4), date(1905,  4, 24),
        date(1906,  4, 16), date(1907,  4,  1), date(1908,  4, 20), date(1909,  4, 12), date(1910,  3, 28),
        date(1911,  4, 17), date(1912,  4,  8), date(1913,  3, 24), date(1914,  4, 13), date(1915,  4,  5),
        date(1916,  4, 24), date(1917,  4,  9), date(1918,  4,  1), date(1919,  4, 21), date(1920,  4,  5),
        date(1921,  3, 28), date(1922,  4, 17), date(1923,  4,  2), date(1924,  4, 21), date(1925,  4, 13),
        date(1926,  4,  5), date(1927,  4, 18), date(1928,  4,  9), date(1929,  4,  1), date(1930,  4, 21),
        date(1931,  4,  6), date(1932,  3, 28), date(1933,  4, 17), date(1934,  4,  2), date(1935,  4, 22),
        date(1936,  4, 13), date(1937,  3, 29), date(1938,  4, 18), date(1939,  4, 10), date(1940,  3, 25),
        date(1941,  4, 14), date(1942,  4,  6), date(1943,  4, 26), date(1944,  4, 10), date(1945,  4,  2),
        date(1946,  4, 22), date(1947,  4,  7), date(1948,  3, 29), date(1949,  4, 18), date(1950,  4, 10),
        date(1951,  3, 26), date(1952,  4, 14), date(1953,  4,  6), date(1954,  4, 19), date(1955,  4, 11),
        date(1956,  4,  2), date(1957,  4, 22), date(1958,  4,  7), date(1959,  3, 30), date(1960,  4, 18),
        date(1961,  4,  3), date(1962,  4, 23), date(1963,  4, 15), date(1964,  3, 30), date(1965,  4, 19),
        date(1966,  4, 11), date(1967,  3, 27), date(1968,  4, 15), date(1969,  4,  7), date(1970,  3, 30),
        date(1971,  4, 12), date(1972,  4,  3), date(1973,  4, 23), date(1974,  4, 15), date(1975,  3, 31),
        date(1976,  4, 19), date(1977,  4, 11), date(1978,  3, 27), date(1979,  4, 16), date(1980,  4,  7),
        date(1981,  4, 20), date(1982,  4, 12), date(1983,  4,  4), date(1984,  4, 23), date(1985,  4,  8),
        date(1986,  3, 31), date(1987,  4, 20), date(1988,  4,  4), date(1989,  3, 27), date(1990,  4, 16),
        date(1991,  4,  1), date(1992,  4, 20), date(1993,  4, 12), date(1994,  4,  4), date(1995,  4, 17),
        date(1996,  4,  8), date(1997,  3, 31), date(1998,  4, 13), date(1999,  4,  5), date(2000,  4, 24),
        date(2001,  4, 16), date(2002,  4,  1), date(2003,  4, 21), date(2004,  4, 12), date(2005,  3, 28),
        date(2006,  4, 17), date(2007,  4,  9), date(2008,  3, 24), date(2009,  4, 13), date(2010,  4,  5),
        date(2011,  4, 25), date(2012,  4,  9), date(2013,  4,  1), date(2014,  4, 21), date(2015,  4,  6),
        date(2016,  3, 28), date(2017,  4, 17), date(2018,  4,  2), date(2019,  4, 22), date(2020,  4, 13),
        date(2021,  4,  5), date(2022,  4, 18), date(2023,  4, 10), date(2024,  4,  1), date(2025,  4, 21),
        date(2026,  4,  6), date(2027,  3, 29), date(2028,  4, 17), date(2029,  4,  2), date(2030,  4, 22),
        date(2031,  4, 14), date(2032,  3, 29), date(2033,  4, 18), date(2034,  4, 10), date(2035,  3, 26),
        date(2036,  4, 14), date(2037,  4,  6), date(2038,  4, 26), date(2039,  4, 11), date(2040,  4,  2),
        date(2041,  4, 22), date(2042,  4,  7), date(2043,  3, 30), date(2044,  4, 18), date(2045,  4, 10),
        date(2046,  3, 26), date(2047,  4, 15), date(2048,  4,  6), date(2049,  4, 19), date(2050,  4, 11),
        date(2051,  4,  3), date(2052,  4, 22), date(2053,  4,  7), date(2054,  3, 30), date(2055,  4, 19),
        date(2056,  4,  3), date(2057,  4, 23), date(2058,  4, 15), date(2059,  3, 31), date(2060,  4, 19),
        date(2061,  4, 11), date(2062,  3, 27), date(2063,  4, 16), date(2064,  4,  7), date(2065,  3, 30),
        date(2066,  4, 12), date(2067,  4,  4), date(2068,  4, 23), date(2069,  4, 15), date(2070,  3, 31),
        date(2071,  4, 20), date(2072,  4, 11), date(2073,  3, 27), date(2074,  4, 16), date(2075,  4,  8),
        date(2076,  4, 20), date(2077,  4, 12), date(2078,  4,  4), date(2079,  4, 24), date(2080,  4,  8),
        date(2081,  3, 31), date(2082,  4, 20), date(2083,  4,  5), date(2084,  3, 27), date(2085,  4, 16),
        date(2086,  4,  1), date(2087,  4, 21), date(2088,  4, 12), date(2089,  4,  4), date(2090,  4, 17),
        date(2091,  4,  9), date(2092,  3, 31), date(2093,  4, 13), date(2094,  4,  5), date(2095,  4, 25),
        date(2096,  4, 16), date(2097,  4,  1), date(2098,  4, 21), date(2099,  4, 13), date(2100,  3, 29),
        date(2101,  4, 18), date(2102,  4, 10), date(2103,  3, 26), date(2104,  4, 14), date(2105,  4,  6),
        date(2106,  4, 19), date(2107,  4, 11), date(2108,  4,  2), date(2109,  4, 22), date(2110,  4,  7),
        date(2111,  3, 30), date(2112,  4, 18), date(2113,  4,  3), date(2114,  4, 23), date(2115,  4, 15),
        date(2116,  3, 30), date(2117,  4, 19), date(2118,  4, 11), date(2119,  3, 27), date(2120,  4, 15),
        date(2121,  4,  7), date(2122,  3, 30), date(2123,  4, 12), date(2124,  4,  3), date(2125,  4, 23),
        date(2126,  4, 15), date(2127,  3, 31), date(2128,  4, 19), date(2129,  4, 11), date(2130,  3, 27),
        date(2131,  4, 16), date(2132,  4,  7), date(2133,  4, 20), date(2134,  4, 12), date(2135,  4,  4),
        date(2136,  4, 23), date(2137,  4,  8), date(2138,  3, 31), date(2139,  4, 20), date(2140,  4,  4),
        date(2141,  3, 27), date(2142,  4, 16), date(2143,  4,  1), date(2144,  4, 20), date(2145,  4, 12),
        date(2146,  4,  4), date(2147,  4, 17), date(2148,  4,  8), date(2149,  3, 31), date(2150,  4, 13),
        date(2151,  4,  5), date(2152,  4, 24), date(2153,  4, 16), date(2154,  4,  1), date(2155,  4, 21),
        date(2156,  4, 12), date(2157,  3, 28), date(2158,  4, 17), date(2159,  4,  9), date(2160,  3, 24),
        date(2161,  4, 13), date(2162,  4,  5), date(2163,  4, 25), date(2164,  4,  9), date(2165,  4,  1),
        date(2166,  4, 21), date(2167,  4,  6), date(2168,  3, 28), date(2169,  4, 17), date(2170,  4,  2),
        date(2171,  4, 22), date(2172,  4, 13), date(2173,  4,  5), date(2174,  4, 18), date(2175,  4, 10),
        date(2176,  4,  1), date(2177,  4, 21), date(2178,  4,  6), date(2179,  3, 29), date(2180,  4, 17),
        date(2181,  4,  2), date(2182,  4, 22), date(2183,  4, 14), date(2184,  3, 29), date(2185,  4, 18),
        date(2186,  4, 10), date(2187,  3, 26), date(2188,  4, 14), date(2189,  4,  6), date(2190,  4, 26),
        date(2191,  4, 11), date(2192,  4,  2), date(2193,  4, 22), date(2194,  4,  7), date(2195,  3, 30),
        date(2196,  4, 18), date(2197,  4, 10), date(2198,  3, 26), date(2199,  4, 15)
      });
    } // namespace global

    namespace US {

      const date reagans_funeral(2004,Jun,11);
      const date sep11_2001(2011,Sep,11);
      const date fords_funeral(2007,Jan,2);
      const date blackout_1977(1977,Jul,14);
      const date johnsons_funeral(1973,Jan,25);
      const date trumans_funeral(1972,Dec,28);
      const date lunar_exploration_day(1969,Jul,21);
      const date eisenhowers_funeral(1969,Mar,31);
      const date snow_storm1969(1969,Feb,10);
      const date day_after_independence_day(1968,Jul,5);
      const date nixons_funeral(1994,Apr,27);
    } // namespace US

    namespace UK {
      const date golden_jubilee_bank_holiday_2002(2002,Jun,3);
      const date special_spring_bank_holiday_2002(2002,Jun,3);
      const date royal_wedding_bank_holiday_2011(2011,Apr,29);
      const date diamond_jubilee_bank_holiday_2012(2012,Jun,4);
      const date special_spring_bank_holiday_2012(2012,Jun,5);
      const date dec31_1999(1999,Dec,31);
    } // namespace UK

  } // namespace holidays
} // namespace logiql
