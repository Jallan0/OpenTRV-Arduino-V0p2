SNAPSHOT of COHEAT functionality 2016/01/31.
DHD20160201

(Updated OTRadioLink.zip, eg with improved internal release notes.)

Snapshot of OpenTRV and OTRadioLink and OTProtocolCC (re)tagged with:

    20160131-COHEAT-dual-channel-beta
and then:
    20160131-COHEAT-dual-channel-beta2

New feature:

  * REV2<->REV9 channel uses new 57600bps GFSK channel; 5kbps OOK channel used only for FS20/FHT8V.


I have tested the current COHEAT functionality:

  * FHT8V control by REV9
  * alert/poll/response radio traffic
  * UI button & LEDS on REV9

Not tested as of 2016/02/01 10:00 UTC:

  * Interaction of window switch and POST.
  * External verification of effective channel separation / non-interference.