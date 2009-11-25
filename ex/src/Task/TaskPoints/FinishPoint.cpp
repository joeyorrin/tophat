/* Generated by Together */

#include "FinishPoint.hpp"
#include <stdlib.h>
#include <assert.h>

bool 
FinishPoint::transition_enter(const AIRCRAFT_STATE & ref_now, 
                              const AIRCRAFT_STATE & ref_last)
{
  bool entered = ObservationZone::transition_enter(ref_now, ref_last);
  if (entered && !has_entered() && get_previous()->has_entered()) {
    set_state_entered(ref_now);
    // only save first enter of finish
  }
  return entered;
}

double
FinishPoint::getElevation() const
{
  return Elevation+task_behaviour.safety_height_arrival;
}


void 
FinishPoint::set_neighbours(OrderedTaskPoint* prev,
                           OrderedTaskPoint* next)
{
  assert(next==NULL);
  // should not ever have an outbound leg
  OrderedTaskPoint::set_neighbours(prev, next);
}

bool 
FinishPoint::equals(const OrderedTaskPoint* other) const
{
  if (dynamic_cast<const FinishPoint*>(other)) {
    return OrderedTaskPoint::equals(other);
  } else {
    return false;
  }
}
