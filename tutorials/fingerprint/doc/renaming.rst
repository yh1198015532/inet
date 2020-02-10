.. :orphan:

Renaming
========

.. - rename modules in the model
   - the fingerprint breaks because by default its tplx (or is it ?)
   - so drop the p (full path) from the ingredients
   - rerun fingerprints without p
   - make the change
   - the fingerprints match



.. sturcture

   - X change breaks fingerprint
   - because something
   - solution
   - example

1. change or action
2. phenomenon / effect
3. solution
4. example

Renaming modules can cause the fingerprints to change, because the default ingredients (``tplx``) contain the full path, thus the module name as well. Renaming modules can cause regression in some cases, e.g. when some functionality in the model depends on module names.

The renaming of NED parameters can also cause regression; the parameter might be used by submodules;
a parameter setting in a derivative module might not have the effect it had before; forgetting to update ini keys can also cause problems.

The renaming of NED parameters can also cause regression:

- The parameter might be used by submodules
- A parameter setting in a derivative module might not have the effect it had before
- Forgetting to update ini keys can also cause problems

.. TODO renaming parameters

.. TODO false positive

.. TODO example for false positive

To filter out false positives for regression, the fingerprints need to be calculated without the full path:

- Before making the change, rerun fingerprints without the full path ingredient
- Update fingerprints, as the new values can be accepted since no change taken place
- Perform renaming
- Run fingerprints again

-----------------------

- Before making the change, rerun fingerprints without the full path ingredient
- Update fingerprints, as the new values can be accepted since no change in the model has taken place
- Perform renaming
- Run fingerprints again

.. --------------------------

  - Before making the change, rerun fingerprints without the full path ingredient (to do that, just delete the ``p`` from the ingredients. The fingerprint tool will calculate the fingerprints using ``tlx``)
  - Update fingerprints (Overwrite fingerprintshowcase.csv with fingerprintshowcase.csv.UPDATED), as the new values can be accepted since no change taken place
  - Perform renaming
  - Run fingerprints again

.. **TODO** run fingerprints with tlx: just delete the p from the csv file and rerun the fingerprints
   now the tlx fingerprints will be calculated...of course they are wrong because the values are from the previous tplx run...so overwrite

.. note:: To run fingerprints with ``tlx``, delete the ``p`` from the ingredient in the .csv file. When the fingerprint test is run again, the fingerprints will be calculated with the new ingredients. The tests will fail, as the values are still the ones calculated with ``tplx``, but it is safe to overwrite them with the updated values, as the model didn't change.

**TODO** should this be somewhere else ?

.. Now, if fingerprints don't pass, it indicates that the change really broke something in the model/introduced a regression.

If the fingerprint tests don't pass, it indicates that the change really broke something in the model and introduced a regression.

.. **TODO** example for a false-positive

As an example for a false-positive, we rename the ``eth`` module vector to ``ethernet`` in :ned:`LinkLayerNodeBase` and :ned:`NetworkLayerNodeBase`. This change affects all host-types such as :ned:`StandardHost` and :ned:`AdhocHost` since they are derivative modules:

.. TODO example for no regression (rename some module)

.. literalinclude:: ../LinkLayerNodeBase.ned.modified
   :diff: ../LinkLayerNodeBase.ned.orig

.. literalinclude:: ../NetworkLayerNodeBase.ned.modified
   :diff: ../NetworkLayerNodeBase.ned.orig

As expected, when running the fingerprints/fingerprint tests, they fail:

.. **TODO** fingerprint FAILED

.. code-block:: fp

  $ inet_fingerprinttest
  . -f omnetpp.ini -c Wired -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c Mixed -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c Wireless -r 0  ... : PASS
  . -f omnetpp.ini -c MixedNID -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WirelessNID -r 0  ... : PASS
  . -f omnetpp.ini -c WiredNID -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c Ospf -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WirelessDim -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessNIDDim -r 0  ... : PASS

We revert the change, then run the fingerprints/fingerprint tests with ingredients ``tlx``, and update ``fingerprintshowcase.csv`` with the new values:

.. **TODO** csv

.. code-block::

  .,        -f omnetpp.ini -c Wireless -r 0,        5s,         d477-98c9/tlx, PASS,
  .,        -f omnetpp.ini -c Mixed -r 0,           5s,         2057-99b2/tlx, PASS,
  .,        -f omnetpp.ini -c Wired -r 0,           5s,         b39c-715b/tlx, PASS,
  .,        -f omnetpp.ini -c WirelessNID -r 0,     5s,         d410-0d99/NID, PASS,
  .,        -f omnetpp.ini -c WiredNID -r 0,        5s,         1145-0392/NID, PASS,
  .,        -f omnetpp.ini -c MixedNID -r 0,        5s,         d2fb-2f48/NID, PASS,
  .,        -f omnetpp.ini -c WirelessNIDDim -r 0,  5s,         d410-0d99/NID, PASS,
  .,        -f omnetpp.ini -c WirelessDim -r 0,     5s,         d477-98c9/tlx, PASS,
  .,        -f omnetpp.ini -c Ospf -r 0,            5000s,      0cf5-6ae4/tlx, PASS,

After making the change and running the fingerprints, they pass:

.. **TODO** fingerprint PASS

.. code-block:: fp

  $ inet_fingerprinttest
  . -f omnetpp.ini -c Wired -r 0  ... : PASS
  . -f omnetpp.ini -c Mixed -r 0  ... : PASS
  . -f omnetpp.ini -c Wireless -r 0  ... : PASS
  . -f omnetpp.ini -c MixedNID -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessNID -r 0  ... : PASS
  . -f omnetpp.ini -c WiredNID -r 0  ... : PASS
  . -f omnetpp.ini -c Ospf -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessDim -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessNIDDim -r 0  ... : PASS

.. ----

.. TODO example for regression (rename some module that is referred to by name, such as ip or routing table) -> leads to an error rather than failed fingerprints

.. maybe renaming a host or something? that is not a src/inet ned change

The following is an example for a parameter name change causing a real regression (as opposed to a false positive). The :ned:`Router` module sets the :par:`forwarding` parameter to ``true`` which it inherits from the :ned:`NetworkLayerNodeBase` module it extends. The latter uses the parameter to enable forwarding in its various submodules, such as :ned:`Ipv4` and :ned:`Ipv6`:

.. code-block:: ned
   :emphasize-lines: 6

   module Router extends ApplicationLayerNodeBase
   {
    parameters:
        @display("i=abstract/router");
        @figure[submodules];
        forwarding = true;
        bool hasOspf = default(false);
        ....

.. code-block:: ned
   :emphasize-lines: 9

   module NetworkLayerNodeBase extends LinkLayerNodeBase
   {
    parameters:
        bool hasIpv4 = default(true);
        bool hasIpv6 = default(false);
        bool hasGn = default(false);
        bool forwarding = default(false);
        bool multicastForwarding = default(false);
        *.forwarding = forwarding;
        *.multicastForwarding = multicastForwarding;
        ....

.. We rename the ``forwarding`` parameter in :ned:`NetworkLayerNodeBase` to ``unicastForwarding``.
   Now, the ``forwarding = true`` key in Router doesn't take effect in the router's submodules,
   and the router doesn't forward packets. (simulations break)(fingerprints break)

**TODO** is the .... needed?

In :ned:`NetworkLayerNodeBase`, we rename the ``forwarding`` parameter  to ``unicastForwarding``.
Now, the ``forwarding = true`` key in :ned:`Router` doesn't take effect in the router's submodules,
and the router doesn't forward packets.

.. (simulations break)(fingerprints break)

.. Results

.. literalinclude:: ../NetworkLayerNodeBase.ned.forwarding
   :diff: ../NetworkLayerNodeBase.ned.orig

.. code-block:: ned
   :emphasize-lines: 6

   module Router extends ApplicationLayerNodeBase
   {
    parameters:
        @display("i=abstract/router");
        @figure[submodules];
        forwarding = true;
        bool hasOspf = default(false);
        ....

.. TODO this breaks tlx fingerprints

.. This change causes also the ``tlx`` fingerprints to fail, thus indicating a regression.
   When we rename the ``forwarding`` parameter in Router to ``unicastForwarding``, the fingerprints pass.

This model change breaks ``tplx`` and even ``tlx`` fingerprints, thus indicating a regression.
When we rename the ``forwarding`` parameter in Router to ``unicastForwarding``, the fingerprints pass.

.. TODO pass

.. TODO fail ?

.. TODO or none of them is needed
