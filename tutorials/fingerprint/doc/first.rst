.. :orphan:

About Fingerprint Testing
=========================

.. About fingerprints in more detail
   ---------------------------------

.. Fingerprint testing is a useful and low-cost tool for regression testing during model development.
   A fingerprint is a hash value, which is calculated during a simulation run from certain properties of the simulation, such as time of events, module names, packet data, etc.

.. Fingerprint testing is a useful and low-cost tool for regression testing during model development.

A fingerprint is a hash value, which is calculated during a simulation run from specified "ingredients", i.e. properties of the simulation such as time of events, module names, packet data, etc.
The hash is updated at each event which takes part in the fingerprint calculation (as defined by the ingredients, filtering, etc) until the end of the simulation (or some defined time limit),
resulting in a fingerprint value.
This value is characteristic of the simulation's trajectory; a fingerprint change indicates a change in the trajectory.

.. **TODO** it is updated at each event/each event which takes part in the fingerprint calculation (as defined by the ingredients, filtering, etc)

.. **V2** This value is characteristic of the simulation's trajectory. It is useful for regression testing because a change in the fingerprint after a change in the model means the trajectory changed.
   It is useful during development to see if some change in the model breaks the model's correct behavior.

  TODO: the workflow is calculate the fingerprint when the model is assumed to work correctly,
  before introducing a change. After the change, run the fingerprint test again, and see if the
  fingerprints match. if not, the change likely broke something in the model.
  One needs to examine if the change in fact did break something, or was expected.
  Running a fingerprint with other ingredients might help verify that the model is correct.
  -> later

.. **- what are the various ingredients? and where to find them**

  .. TODO: maybe this shouldnt be here but in one of the steps

  The fingerprint ingredients are actually can be specified...

  the fingerprint is a 32 bit value, and also it contains the ingredients, which are denoted by a letter

  such as abcd-ef01-1248-abcd/tplx -> more like 32 bits

  the list of ingredients are in the manual

.. The fingerprint is a 32-bit hexadecimal value and upended by the ingredients used for calculating it, denoted by letters:

The fingerprint contains a 32-bit hexadecimal hash value and the ingredients used for calculating it, denoted by letters. Here is an example:

.. TODO: example fingerprint

.. code-block:: text

   53de-64a7/tplx

In this example, ``t`` means time of event, ``p`` the full path of modules, ``l`` the message length, and ``x`` the extra data added programatically. Other possible ingredients include various properties of messages, modules and results. For the complete list, check out the `Fingerprint section <https://doc.omnetpp.org/omnetpp/manual/#sec:testing:fingerprint-tests>`_ in the OMNeT++ Simulation Manual.

.. TODO tplx is a default

The fingerprints can be specified in the ini file for each configuration. Specifying any fingerprint enables fingerprint calculation for the simulation. For example:

.. if a fingerprint is specified, it will be calculated. so if you wanna calculate the fingerprint for a config X,
   you just say:

  | [Config X]
  | network = Y
  | fingerprint = 0000-0000/tplx

.. code-block:: ini

   [Config Ethernet]
   network = Wired
   fingerprint = 0000-0000/tplx

.. you just specify a value and the ingredients and it will be calculated and the 0000-0000 can be replaced by the resulting value.

The fingerprint will be calculated for that simulation when run in Qtenv or Cmdenv.
Qtenv and Cmdenv indicate whether the fingerprint is verified, and print the calculated fingerprint value. The original value can be replaced with the resulting one in the ini file.

.. the calculated value is printed. The original value can be replaced with the resulting one in the ini file.

.. TODO: qtenv prints the fingerprint

.. also, the fingerprint is calculated whether the simulation is run with qtenv or from the command line.

.. TODO fingerprint successfully verified

.. However, there is a more convenient way in INET, the fingerprint tool.

.. It automates the process to help with development.

INET's fingerprint test tool automates this process, making it easier to work with many simulations and fingerprints.

The fingerprint tool
--------------------

..  - the fingerprint tool can automate the process
  - its a command line tool, found in inet/tests/fingerprint -> actually, its inet/bin
  - its the inet_fingerprinttest script

  - csv file format
  - reports PASS, FAIL or ERROR
  - creates files
  - can be updated by overwriting
  - can be run in release or debug
  - can be filtered with -m which is a regex?
  - for more info -h

The fingerprint tool is a conventient way to run fingerprint tests. It is located in the ``inet/bin`` folder, and when the ``inet`` directory is added to the PATH, it can be run from any directory (inet subdirectory?).

The fingerprint test tool uses .csv files to run fingerprint tests.
A line in the .csv file defines a simulation run by specifying the working directory, command line arguments, sim time limit, fingerprint+ingredients, expected result, and tags.
The result can either be PASS, FAIL or ERROR.

  By default, the fingerprint test tool runs all simulations defined in .csv files in the current folder.TODO later
  The set of simulations can be filtered with the ``-m`` command line option.

When run without arguments, the fingerprint test tool runs all tests in all .csv files in the current directory. A .csv file can be specified with the first argument.
Also, the set of tests to run can be filtered with the ``-m`` command line option, which matches regex? TODO.
For the list of all available options, run the tool with the ``-h`` argument.

.. Note that ``-h`` lists all available options.

.. The first argument specifies a .csv file.

.. **TODO** the script runs all tests in all .csv files in the current directory by default/if otherwise specified
.. for example, a .csv file can be added as an argument. or the -m to filter
   it appends UPDATED FAILED ERROR to the .csv filename so xy.csv.UPDATED

.. A line in the .csv file defines a simulation run, by specifying the working directory, command line arguments, sim time limit, fingerprint+ingredients, expected result, and tags.
   The result can either be PASS, FAIL or ERROR.

**V1** When the tests are finished, and not all of them passed, the tool creates additional .csv files;
it appends UPDATED, FAILED, or ERROR to the original .csv file's name:

- The UPDATED file contains the updated fingerprint values for all tests
- The FAILED file contains only those lines which failed
- The ERROR file contains only those lines which resulted in an error

.. When the tests are finished, the tool creates an additional .csv file, with "UPDATED" appended to the .csv file's name. This contains the

**V2** When the tests are finished, the tool may create additional .csv files (appending UPDATED, FAILED, and ERROR to the .csv file's name):

- an UPDATED file, which has the fingerprints just calculated for all lines
- a FAILED file, which contains just the lines for the failed simulations, with the calculated fingerprint. This file can be used for re-running just the simulations with failed fingerprints
- an ERROR file, which contains the lines for simulations which finished with errors, making it easier to rerun just those simulations

.. /when specifying this file to run


The updated file can be used to overwrite the original one to accept the new fingerprints.

The original first step
-----------------------

  all this fingerprint testing depends on repeatable deterministic simulations, random number generation, etc.
  if it's not repeatable, e.g. emulation, than this whole stuff doesn't apply

  default ingredients is good because there's always a fingerprint sensitive to changes ready-to-be-used for regression testing

  - the configs in the tutorial that will be used to demonstrate the fingerprint tests
  - the csv file
  - they are correct fingerprints
  - the changes are no contained in the tutorial
  - the user is expected to make them and run the fingerprint test to see the results

The tutorial contains several simulations, which will be used to demonstrate how various changes affect fingerprints:

TODO: a list of the configs (just an overview)

The ``fingerprintshowcase.csv`` file in the tutorial's directory containing the fingerprints TODO:

.. .. literalinclude:: ../fingerprintshowcase.csv
      :language: text

.. literalinclude:: ../fingerprintshowcase.csv
   :start-at: sim time limit
   :language: text

.. code-block:: text

  # working directory, command line arguments, simulation time limit, fingerprint, expected result, tags

  .,    -f omnetpp.ini -c Ethernet -r 0,       0.2s,     4500-0673/tplx, PASS,	EasyToHandleChanges RenamingSubmodule RenamingParameter ChangingPacketLength AddingNewEvents1 AddingNewEvents2 AcceptingFPChanges
  .,    -f omnetpp.ini -c EthernetUdp10 -r 0,  0.2s,     ea97-154f/tplx, PASS,	ChangingPacketLength
  .,    -f omnetpp.ini -c Wifi -r 0,             5s,     791d-aba6/tplx, PASS,	EasyToHandleChanges RenamingSubmodule ChangingPacketLength ChangingTimer AddingNewEvents1 AddingNewEvents2 AcceptingFPChanges
  .,    -f omnetpp.ini -c WifiUdp10 -r 0,        5s,     d801-fc01/tplx, PASS,	ChangingPacketLength

.. **V1** The .csv file contains the correct fingerprints **TODO** what does that mean?. The changes mentioned in the tutorial are not contained in the anywhere, the user is expected to make them and run the fingerprint tests to see how the model changes affect the fingerprints.

.. The .csv file contains the correct fingerprints **TODO** what does that mean?. The user is expected to make the changes and run the fingerprint tests to see how the model changes affect the fingerprints.

The .csv file contains the correct fingerprints, i.e. they all pass. To try the examples, the user is expected to make the changes described in the tutorial (or something similar/something else/some other changes/different changes) and run the fingerprint tests to see how the model changes affect the fingerprints.

TODO its for experimentation

The fingerprints can be run from the command line. Make sure to run ``. setenv`` in both the ``omnetpp`` and ``inet`` folders:

.. code-block:: bash

   $ cd ~/workspace/omnetpp
   $ . setenv
   $ cd ~/workspace/inet
   $ . setenv
   $ cd ~/workspace/inet/tutorials/fingerprint
   $ inet_fingerprinttest

.. TODO: the setenv and the fingerprinttest separately ?

The ``inet_fingerprinttest`` runs all simulations specified in all .csv files in the currect folder:

.. code-block:: fp

  $ inet_fingerprinttest
  . -f omnetpp.ini -c Ethernet -r 0 ... : PASS
  . -f omnetpp.ini -c EthernetUdp10 -r 0 ... : PASS
  . -f omnetpp.ini -c Wifi -r 0 ... : PASS
  . -f omnetpp.ini -c WifiUdp10 -r 0 ... : PASS

  ----------------------------------------------------------------------
  Ran 4 tests in 12.451s

  OK

  Log has been saved to test.out
  Test results equals to expected results

.. figure:: media/1.png
   :width: 80%
   :align: center

TODO rules of thumb, default fingerprints, workflow, resetting
