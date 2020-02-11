.. :orphan:

New events - NID
================

.. Another way of dealing with new events is to use the network communication fingerprint calculator.

.. When a change introduces new events to the simulation and breaks fingerprints, an option is to use a different / alternative fingerprint calculator, not the default one. INET features the Network Communication Fingerprint Calculator, which extends the default one (as that normal fingerprints can be used alongside it). This fingerprint calculator uses the communication between modules, such as messages, etc, TODO, as ingredients. TODO

   This only takes into account/uses the communication between nodes.
   Thus protocol implementation details don't matter...only the data content of the packets.
   The fingerprint calculator has three available ingredients:

When a change introduces new events to the simulation and breaks fingerprints, an option is to use an alternative fingerprint calculator instead of the default one. INET features the Network Communication Fingerprint Calculator, which extends the default calculator, and adds new ingredients that can be used alongside the default ones.

.. This fingerprint calculator uses only the communication between network nodes to calculate fingerprints.

.. This fingerprint calculator uses the communication between network nodes as ingredients.

.. The calculator only takes into account the communication between the network nodes.

.. Thus protocol implementation details don't affect the fingerprints, only the data content of the packets. (doesn't matter what happens/what events there are inside network nodes TODO)

The calculator uses the communication between the network nodes to calculate fingerprints.
Thus protocol implementation details and events inside network nodes don't affect the fingerprints, only the data content of the packets.
The fingerprint calculator has three available ingredients:

.. - ``N``: Network node path in the module hierarchy
   - ``I``: Network interface path in the module hierarchy
   - ``D``: Network data

- ``N``: Network node path in the module hierarchy
- ``I``: Network interface path in the module hierarchy; the superset of ``N``
- ``D``: Network data

.. The network node path is a subset of the network interface path, as the latter is more specific, and contains the network node path. Note that the ``D`` network data is

.. note:: Both ``d`` and ``D`` are network data ingredients; ``d`` includes packet data and meta-infos such as annotations, tags, and flags; ``D`` includes just the packet data.

To use the ``NID`` ingredients, add the following line to the ``General`` configuration:

.. literalinclude:: ../omnetpp.ini
   :start-at: General
   :end-at: class
   :language: ini

.. .. literalinclude:: ../omnetpp.ini
      :start-at: General
      :end-at: class
      :language: ini
      :emphasize-lines: 2

.. TODO the default and the NID can be mixed

Now, the ``NID`` and the default ingredients can be mixed.

- also, filtering is slower because the filter expression needs to be evaluated for each item
- if ``t`` is not in the ingredients, only D, then just the order of the packet datas matter

TODO its the same as the previous step

To filter the effects of new events, run fingerprints with NID ingredients:

- Before making the change in the model, run the fingerprint with NID ingredients only
- Make the changes in the model
- Run the fingerprint tests again

If fingerprint tests pass, there was no change in the communication between network nodes,
and the model can be assumed to be correct.

.. TODO example

---------------------------

As a simplistic example, we will make the same change to the Udp module as in the previous step.
We will use only the NID ingredients to calculate fingerprints, and verify the model.

We run the fingerprints with NID ingredients by replacing the ingredients in the .csv file:

TODO

As there was no change in the model, the new fingerprints can be accepted:

.. code-block:: fp

   $ mv fingerprintshowcase.csv.UPDATED fingerprintshowcase.csv

We make the change:

.. literalinclude:: ../Udp_mod.cc
   :diff: ../Udp_orig.cc

We run the fingerprints again TODO

TODO

.. Here is the example model change from the previous step:

.. .. literalinclude:: ../Udp_mod.cc
      :diff: ../Udp_orig.cc

.. We run the fingerprint tests with only the NID ingredients, and update the .csv file with the new values:

.. TODO NID fingerprints PASS

After making the change, the fingerprint tests still pass, thus the model can be assumed correct.

TODO pittfalls
