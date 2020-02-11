.. :orphan:

Changing Packet Length
======================

.. TODO

tplx -> tpx
ha csak mondjuk az app csomaghossza valtozott 1-rol 2-byte-ra, ethernet padding miatt min csomag length 64
vagy
tplx -> px
ha nagyobb a valtozas

workflow -> ha megváltoztatjuk a csomag hosszát de belefér a min ehternet frame-be akkor az az expectation hogy nem változik meg a fingerprint (a csomag hossza a network-ön nem változik) és így az időzítések se
de ha nagy a változás akkor igen

TODO minden stepnél -> expectation -> a mögöttes gondolkodás

l -> minden eseménynél figyelembe veszi a csomag hosszát

mit gondolsz az adott change-nél
