#include "test.hpp"
#include <boost/ut.hpp>

void run_event_queue_event_time_stamp_test(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "event_time_stamp"_test = [] {
    {
      krbn::event_queue::event_time_stamp event_time_stamp1(krbn::absolute_time_point(100),
                                                            krbn::absolute_time_duration(10));
      krbn::event_queue::event_time_stamp event_time_stamp2(krbn::absolute_time_point(200),
                                                            krbn::absolute_time_duration(10));
      krbn::event_queue::event_time_stamp event_time_stamp3(krbn::absolute_time_point(100),
                                                            krbn::absolute_time_duration(20));
      krbn::event_queue::event_time_stamp event_time_stamp4(krbn::absolute_time_point(200),
                                                            krbn::absolute_time_duration(20));

      expect(event_time_stamp1.get_time_stamp() == krbn::absolute_time_point(100));
      expect(event_time_stamp1.get_input_delay_duration() == krbn::absolute_time_duration(10));

      expect(event_time_stamp2.get_time_stamp() == krbn::absolute_time_point(200));
      expect(event_time_stamp2.get_input_delay_duration() == krbn::absolute_time_duration(10));

      expect(event_time_stamp3.get_time_stamp() == krbn::absolute_time_point(100));
      expect(event_time_stamp3.get_input_delay_duration() == krbn::absolute_time_duration(20));

      expect(event_time_stamp4.get_time_stamp() == krbn::absolute_time_point(200));
      expect(event_time_stamp4.get_input_delay_duration() == krbn::absolute_time_duration(20));

      expect(event_time_stamp1 == event_time_stamp1);
      expect(event_time_stamp1 != event_time_stamp2);
      expect(event_time_stamp1 != event_time_stamp3);
      expect(event_time_stamp1 != event_time_stamp4);

      krbn::event_queue::event_time_stamp copy1(event_time_stamp1);
      auto copy2 = event_time_stamp1;

      expect(event_time_stamp1 == copy1);
      expect(event_time_stamp1 == copy2);
    }
  };
}
