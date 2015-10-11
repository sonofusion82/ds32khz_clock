#!/usr/bin/python

import time

t = time.localtime()
seconds_since_midnight = t.tm_sec + (t.tm_min * 60) + (t.tm_hour * 3600)

with open('current_timestamp.h', 'w') as f:
    f.write('#define BUILD_TIME_SINCE_MIDNIGHT %d\n' % seconds_since_midnight)
    f.write('#define UNIX_TIMESTAMP %d\n' % time.time())
