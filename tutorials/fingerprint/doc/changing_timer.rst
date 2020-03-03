.. :orphan:

Changing a Timer
================

  TODO: find a module where we can change the interval of a timer
  e.g. RadioMedium removeNonInterfering...
  to change interval: change maxTransmissionDuration in mediumLimitCache

  TODO: if you filter out this message, recompute fingerprints before changing, do the change and the tests PASS, then accept, etc.

  filter out how ? by message name or by radio medium module

.. Changes in a model's timers might break fingerprints, but otherwise wouldn't invalidate the model.
   For example, there are timers which don't affect the behavior of the model.

Some changes in a model's timers might break fingerprints, but otherwise wouldn't invalidate the model, e.g. timers which don't affect the model's behavior.
However, the change in the timers might break the default ingredient fingerprint tests.
In such case, the events or modules that contain the timer need to be filtered:

- Before making the change in the model, filter the events happening in the affected module/filter the affected module, and calculate the fingerprints

**TODO** or filter the modules

- Before making the change, filter the events which involve the affected timer, and calculate the fingerprints
- Accept the new fingerprint values
- Make the change
- Rerun the fingerprint tests

The tests should pass.

As a simplistic example, we'll change how the ``removeNonInterferingTransmissionsTimer`` is scheduled in ``RadioMedium.cc``. **TODO** what does it do and why it doesn't affect the model

We run the fingerprint tests and filter the events in the ``RadioMedium`` module:

.. code-block:: fp

  $ inet_fingerprinttest -a --fingerprint-events='"not name=~removeNonInterferingTransmissions"'
  . -f omnetpp.ini -c Ethernet -r 0  ... : PASS
  . -f omnetpp.ini -c Ospf -r 0  ... : PASS
  . -f omnetpp.ini -c Wifi -r 0  ... : FAILED
  . -f omnetpp.ini -c WifiUdp10 -r 0  ... : FAILED
  . -f omnetpp.ini -c EthernetUdp10 -r 0  ... : PASS

The tests fail because the set of events used to calculate them changed.
Since there was no change in the model, just in how the fingerprints are calculated, the .csv file can be updated with the new values:

.. code-block:: fp

   $ mv fingerprintshowcase.csv.UPDATED fingerprintshowcase.csv

Now, we change the timer:

.. literalinclude:: ../RadioMedium.cc.mod
   :diff: ../RadioMedium.cc.orig

We re-run the fingerprint tests:

.. code-block:: fp

  $ inet_fingerprinttest -a --fingerprint-events='"not name=~removeNonInterferingTransmissions"'
  . -f omnetpp.ini -c Ethernet -r 0  ... : PASS
  . -f omnetpp.ini -c Ospf -r 0  ... : PASS
  . -f omnetpp.ini -c Wifi -r 0  ... : PASS
  . -f omnetpp.ini -c WifiUdp10 -r 0  ... : PASS
  . -f omnetpp.ini -c EthernetUdp10 -r 0  ... : PASS

.. **TODO** The model is verified. Now default fingerprints without filtering can be accepted

The model is verified. The fingerprints can be calculated without filtering, and the .csv file can be updated with the new values. **TODO** details/link to step
