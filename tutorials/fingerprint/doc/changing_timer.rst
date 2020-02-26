.. :orphan:

Changing a Timer
================

TODO: find a module where we can change the interval of a timer
e.g. RadioMedium removeNonInterfering...
to change interval: change maxTransmissionDuration in mediumLimitCache

TODO: if you filter out this message, recompute fingerprints before changing, do the change and the tests PASS, then accept, etc.

filter out how ? by message name or by radio medium module

.. literalinclude:: ../RadioMedium.cc.mod
   :diff: ../RadioMedium.cc.orig
