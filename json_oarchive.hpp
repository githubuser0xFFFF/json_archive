/***************************************************************************
 * Copyright (C) 2015 - 2023 Greedysky Studio

 * Use, modification and distribution is subject to the Boost Software
 * License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt).
 ***************************************************************************/
#pragma once
#include "json_oarchive_impl.hpp"

namespace boost {
namespace archive {
class json_oarchive
{
public:
  json_oarchive(std::ostream& os)
    : output_stream_(os)
    , json_archive_()
  {
  }

public:
  template<class T>
  json_oarchive & operator<<(const T& t)
  {
    json_archive_ << t;
    output_stream_ << json_archive_.get_json_data().dump(2).c_str();
    return *this;
  }

  json_oarchive_impl json_archive_;
  std::ostream&      output_stream_;
};
} // namespace archive
} // namespace boost

