<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.6.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="pinhead" urn="urn:adsk.eagle:library:325">
<description>&lt;b&gt;Pin Header Connectors&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="2X08" urn="urn:adsk.eagle:footprint:22373/1" library_version="4">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-10.16" y1="-1.905" x2="-9.525" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="-2.54" x2="-7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="-2.54" x2="-5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-2.54" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-2.54" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-2.54" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="3.175" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="4.445" y1="-2.54" x2="5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-1.905" x2="-10.16" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="1.905" x2="-9.525" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="2.54" x2="-8.255" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="2.54" x2="-7.62" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="1.905" x2="-6.985" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="2.54" x2="-5.715" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="2.54" x2="-5.08" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="1.905" x2="-4.445" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="2.54" x2="-3.175" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="2.54" x2="-2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.905" x2="-1.905" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="2.54" x2="-0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="2.54" x2="0" y2="1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="1.905" x2="0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="0.635" y1="2.54" x2="1.905" y2="2.54" width="0.1524" layer="21"/>
<wire x1="1.905" y1="2.54" x2="2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="1.905" x2="3.175" y2="2.54" width="0.1524" layer="21"/>
<wire x1="3.175" y1="2.54" x2="4.445" y2="2.54" width="0.1524" layer="21"/>
<wire x1="4.445" y1="2.54" x2="5.08" y2="1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="1.905" x2="5.715" y2="2.54" width="0.1524" layer="21"/>
<wire x1="5.715" y1="2.54" x2="6.985" y2="2.54" width="0.1524" layer="21"/>
<wire x1="6.985" y1="2.54" x2="7.62" y2="1.905" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="5.715" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="1.905" x2="-7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="1.905" x2="-5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.905" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="1.905" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="1.905" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="1.905" x2="5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="7.62" y1="1.905" x2="7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="5.715" y1="-2.54" x2="6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="3.175" y1="-2.54" x2="4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-2.54" x2="1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-2.54" x2="-0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="-2.54" x2="-3.175" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="-2.54" x2="-5.715" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="-2.54" x2="-8.255" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="7.62" y1="1.905" x2="8.255" y2="2.54" width="0.1524" layer="21"/>
<wire x1="8.255" y1="2.54" x2="9.525" y2="2.54" width="0.1524" layer="21"/>
<wire x1="9.525" y1="2.54" x2="10.16" y2="1.905" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-1.905" x2="9.525" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="8.255" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="10.16" y1="1.905" x2="10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="8.255" y1="-2.54" x2="9.525" y2="-2.54" width="0.1524" layer="21"/>
<pad name="1" x="-8.89" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="2" x="-8.89" y="1.27" drill="1.016" shape="octagon"/>
<pad name="3" x="-6.35" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="4" x="-6.35" y="1.27" drill="1.016" shape="octagon"/>
<pad name="5" x="-3.81" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="6" x="-3.81" y="1.27" drill="1.016" shape="octagon"/>
<pad name="7" x="-1.27" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="8" x="-1.27" y="1.27" drill="1.016" shape="octagon"/>
<pad name="9" x="1.27" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="10" x="1.27" y="1.27" drill="1.016" shape="octagon"/>
<pad name="11" x="3.81" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="12" x="3.81" y="1.27" drill="1.016" shape="octagon"/>
<pad name="13" x="6.35" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="14" x="6.35" y="1.27" drill="1.016" shape="octagon"/>
<pad name="15" x="8.89" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="16" x="8.89" y="1.27" drill="1.016" shape="octagon"/>
<text x="-10.16" y="3.175" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-10.16" y="-4.445" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-9.144" y1="-1.524" x2="-8.636" y2="-1.016" layer="51"/>
<rectangle x1="-9.144" y1="1.016" x2="-8.636" y2="1.524" layer="51"/>
<rectangle x1="-6.604" y1="1.016" x2="-6.096" y2="1.524" layer="51"/>
<rectangle x1="-6.604" y1="-1.524" x2="-6.096" y2="-1.016" layer="51"/>
<rectangle x1="-4.064" y1="1.016" x2="-3.556" y2="1.524" layer="51"/>
<rectangle x1="-4.064" y1="-1.524" x2="-3.556" y2="-1.016" layer="51"/>
<rectangle x1="-1.524" y1="1.016" x2="-1.016" y2="1.524" layer="51"/>
<rectangle x1="1.016" y1="1.016" x2="1.524" y2="1.524" layer="51"/>
<rectangle x1="3.556" y1="1.016" x2="4.064" y2="1.524" layer="51"/>
<rectangle x1="-1.524" y1="-1.524" x2="-1.016" y2="-1.016" layer="51"/>
<rectangle x1="1.016" y1="-1.524" x2="1.524" y2="-1.016" layer="51"/>
<rectangle x1="3.556" y1="-1.524" x2="4.064" y2="-1.016" layer="51"/>
<rectangle x1="6.096" y1="1.016" x2="6.604" y2="1.524" layer="51"/>
<rectangle x1="6.096" y1="-1.524" x2="6.604" y2="-1.016" layer="51"/>
<rectangle x1="8.636" y1="1.016" x2="9.144" y2="1.524" layer="51"/>
<rectangle x1="8.636" y1="-1.524" x2="9.144" y2="-1.016" layer="51"/>
</package>
<package name="2X08/90" urn="urn:adsk.eagle:footprint:22374/1" library_version="4">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-10.16" y1="-1.905" x2="-7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="0.635" x2="-10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="0.635" x2="-10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="6.985" x2="-8.89" y2="1.27" width="0.762" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.635" x2="-7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-6.35" y1="6.985" x2="-6.35" y2="1.27" width="0.762" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="6.985" x2="-3.81" y2="1.27" width="0.762" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="6.985" x2="-1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="0" y1="-1.905" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="6.985" x2="1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0.635" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="6.985" x2="3.81" y2="1.27" width="0.762" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="7.62" y1="0.635" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="6.35" y1="6.985" x2="6.35" y2="1.27" width="0.762" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-1.905" x2="10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="10.16" y1="0.635" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="8.89" y1="6.985" x2="8.89" y2="1.27" width="0.762" layer="21"/>
<pad name="2" x="-8.89" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="4" x="-6.35" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="6" x="-3.81" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="8" x="-1.27" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="10" x="1.27" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="12" x="3.81" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="14" x="6.35" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="16" x="8.89" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="1" x="-8.89" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="3" x="-6.35" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="5" x="-3.81" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="7" x="-1.27" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="9" x="1.27" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="11" x="3.81" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="13" x="6.35" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="15" x="8.89" y="-6.35" drill="1.016" shape="octagon"/>
<text x="-10.795" y="-3.81" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="12.065" y="-3.81" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-9.271" y1="0.635" x2="-8.509" y2="1.143" layer="21"/>
<rectangle x1="-6.731" y1="0.635" x2="-5.969" y2="1.143" layer="21"/>
<rectangle x1="-4.191" y1="0.635" x2="-3.429" y2="1.143" layer="21"/>
<rectangle x1="-1.651" y1="0.635" x2="-0.889" y2="1.143" layer="21"/>
<rectangle x1="0.889" y1="0.635" x2="1.651" y2="1.143" layer="21"/>
<rectangle x1="3.429" y1="0.635" x2="4.191" y2="1.143" layer="21"/>
<rectangle x1="5.969" y1="0.635" x2="6.731" y2="1.143" layer="21"/>
<rectangle x1="8.509" y1="0.635" x2="9.271" y2="1.143" layer="21"/>
<rectangle x1="-9.271" y1="-2.921" x2="-8.509" y2="-1.905" layer="21"/>
<rectangle x1="-6.731" y1="-2.921" x2="-5.969" y2="-1.905" layer="21"/>
<rectangle x1="-9.271" y1="-5.461" x2="-8.509" y2="-4.699" layer="21"/>
<rectangle x1="-9.271" y1="-4.699" x2="-8.509" y2="-2.921" layer="51"/>
<rectangle x1="-6.731" y1="-4.699" x2="-5.969" y2="-2.921" layer="51"/>
<rectangle x1="-6.731" y1="-5.461" x2="-5.969" y2="-4.699" layer="21"/>
<rectangle x1="-4.191" y1="-2.921" x2="-3.429" y2="-1.905" layer="21"/>
<rectangle x1="-1.651" y1="-2.921" x2="-0.889" y2="-1.905" layer="21"/>
<rectangle x1="-4.191" y1="-5.461" x2="-3.429" y2="-4.699" layer="21"/>
<rectangle x1="-4.191" y1="-4.699" x2="-3.429" y2="-2.921" layer="51"/>
<rectangle x1="-1.651" y1="-4.699" x2="-0.889" y2="-2.921" layer="51"/>
<rectangle x1="-1.651" y1="-5.461" x2="-0.889" y2="-4.699" layer="21"/>
<rectangle x1="0.889" y1="-2.921" x2="1.651" y2="-1.905" layer="21"/>
<rectangle x1="3.429" y1="-2.921" x2="4.191" y2="-1.905" layer="21"/>
<rectangle x1="0.889" y1="-5.461" x2="1.651" y2="-4.699" layer="21"/>
<rectangle x1="0.889" y1="-4.699" x2="1.651" y2="-2.921" layer="51"/>
<rectangle x1="3.429" y1="-4.699" x2="4.191" y2="-2.921" layer="51"/>
<rectangle x1="3.429" y1="-5.461" x2="4.191" y2="-4.699" layer="21"/>
<rectangle x1="5.969" y1="-2.921" x2="6.731" y2="-1.905" layer="21"/>
<rectangle x1="8.509" y1="-2.921" x2="9.271" y2="-1.905" layer="21"/>
<rectangle x1="5.969" y1="-5.461" x2="6.731" y2="-4.699" layer="21"/>
<rectangle x1="5.969" y1="-4.699" x2="6.731" y2="-2.921" layer="51"/>
<rectangle x1="8.509" y1="-4.699" x2="9.271" y2="-2.921" layer="51"/>
<rectangle x1="8.509" y1="-5.461" x2="9.271" y2="-4.699" layer="21"/>
</package>
</packages>
<packages3d>
<package3d name="2X08" urn="urn:adsk.eagle:package:22481/2" type="model" library_version="4">
<description>PIN HEADER</description>
<packageinstances>
<packageinstance name="2X08"/>
</packageinstances>
</package3d>
<package3d name="2X08/90" urn="urn:adsk.eagle:package:22488/2" type="model" library_version="4">
<description>PIN HEADER</description>
<packageinstances>
<packageinstance name="2X08/90"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="PINH2X8" urn="urn:adsk.eagle:symbol:22372/1" library_version="4">
<wire x1="-6.35" y1="-12.7" x2="8.89" y2="-12.7" width="0.4064" layer="94"/>
<wire x1="8.89" y1="-12.7" x2="8.89" y2="10.16" width="0.4064" layer="94"/>
<wire x1="8.89" y1="10.16" x2="-6.35" y2="10.16" width="0.4064" layer="94"/>
<wire x1="-6.35" y1="10.16" x2="-6.35" y2="-12.7" width="0.4064" layer="94"/>
<text x="-6.35" y="10.795" size="1.778" layer="95">&gt;NAME</text>
<text x="-6.35" y="-15.24" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-2.54" y="7.62" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="2" x="5.08" y="7.62" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="3" x="-2.54" y="5.08" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="4" x="5.08" y="5.08" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="5" x="-2.54" y="2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="6" x="5.08" y="2.54" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="7" x="-2.54" y="0" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="8" x="5.08" y="0" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="9" x="-2.54" y="-2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="10" x="5.08" y="-2.54" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="11" x="-2.54" y="-5.08" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="12" x="5.08" y="-5.08" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="13" x="-2.54" y="-7.62" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="14" x="5.08" y="-7.62" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="15" x="-2.54" y="-10.16" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="16" x="5.08" y="-10.16" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="PINHD-2X8" urn="urn:adsk.eagle:component:22549/4" prefix="JP" uservalue="yes" library_version="4">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="A" symbol="PINH2X8" x="0" y="0"/>
</gates>
<devices>
<device name="" package="2X08">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="10" pad="10"/>
<connect gate="A" pin="11" pad="11"/>
<connect gate="A" pin="12" pad="12"/>
<connect gate="A" pin="13" pad="13"/>
<connect gate="A" pin="14" pad="14"/>
<connect gate="A" pin="15" pad="15"/>
<connect gate="A" pin="16" pad="16"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
<connect gate="A" pin="5" pad="5"/>
<connect gate="A" pin="6" pad="6"/>
<connect gate="A" pin="7" pad="7"/>
<connect gate="A" pin="8" pad="8"/>
<connect gate="A" pin="9" pad="9"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:22481/2"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="POPULARITY" value="6" constant="no"/>
</technology>
</technologies>
</device>
<device name="/90" package="2X08/90">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="10" pad="10"/>
<connect gate="A" pin="11" pad="11"/>
<connect gate="A" pin="12" pad="12"/>
<connect gate="A" pin="13" pad="13"/>
<connect gate="A" pin="14" pad="14"/>
<connect gate="A" pin="15" pad="15"/>
<connect gate="A" pin="16" pad="16"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
<connect gate="A" pin="5" pad="5"/>
<connect gate="A" pin="6" pad="6"/>
<connect gate="A" pin="7" pad="7"/>
<connect gate="A" pin="8" pad="8"/>
<connect gate="A" pin="9" pad="9"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:22488/2"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="POPULARITY" value="0" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1" urn="urn:adsk.eagle:library:371">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="-12V" urn="urn:adsk.eagle:symbol:26932/1" library_version="1">
<wire x1="-1.27" y1="1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="1.27" y2="1.905" width="0.254" layer="94"/>
<wire x1="-1.27" y1="0.635" x2="0" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0" y1="-1.27" x2="1.27" y2="0.635" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="-12V" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
<symbol name="+12V" urn="urn:adsk.eagle:symbol:26931/1" library_version="1">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<wire x1="1.27" y1="-0.635" x2="0" y2="1.27" width="0.254" layer="94"/>
<wire x1="0" y1="1.27" x2="-1.27" y2="-0.635" width="0.254" layer="94"/>
<text x="-2.54" y="-5.08" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="+12V" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="+5V" urn="urn:adsk.eagle:symbol:26929/1" library_version="1">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<text x="-2.54" y="-5.08" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="+5V" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="GND" urn="urn:adsk.eagle:symbol:26925/1" library_version="1">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="-12V" urn="urn:adsk.eagle:component:26961/1" prefix="P-" library_version="1">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="-12V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="+12V" urn="urn:adsk.eagle:component:26959/1" prefix="P+" library_version="1">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="+12V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="+5V" urn="urn:adsk.eagle:component:26963/1" prefix="P+" library_version="1">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="+5V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="GND" urn="urn:adsk.eagle:component:26954/1" prefix="GND" library_version="1">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-molex" urn="urn:adsk.eagle:library:165">
<description>&lt;b&gt;Molex Connectors&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="22-23-2041" urn="urn:adsk.eagle:footprint:8078261/1" library_version="5">
<description>&lt;b&gt;KK® 254 Solid Header, Vertical, with Friction Lock, 4 Circuits, Tin (Sn) Plating&lt;/b&gt;&lt;p&gt;&lt;a href =http://www.molex.com/pdm_docs/sd/022232041_sd.pdf&gt;Datasheet &lt;/a&gt;</description>
<wire x1="-5.08" y1="3.175" x2="5.08" y2="3.175" width="0.254" layer="21"/>
<wire x1="5.08" y1="3.175" x2="5.08" y2="1.27" width="0.254" layer="21"/>
<wire x1="5.08" y1="1.27" x2="5.08" y2="-3.175" width="0.254" layer="21"/>
<wire x1="5.08" y1="-3.175" x2="-5.08" y2="-3.175" width="0.254" layer="21"/>
<wire x1="-5.08" y1="-3.175" x2="-5.08" y2="1.27" width="0.254" layer="21"/>
<wire x1="-5.08" y1="1.27" x2="-5.08" y2="3.175" width="0.254" layer="21"/>
<wire x1="-5.08" y1="1.27" x2="5.08" y2="1.27" width="0.254" layer="21"/>
<pad name="1" x="-3.81" y="0" drill="1" shape="long" rot="R90"/>
<pad name="2" x="-1.27" y="0" drill="1" shape="long" rot="R90"/>
<pad name="3" x="1.27" y="0" drill="1" shape="long" rot="R90"/>
<pad name="4" x="3.81" y="0" drill="1" shape="long" rot="R90"/>
<text x="-5.08" y="3.81" size="1.016" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="-5.08" size="1.016" layer="27" ratio="10">&gt;VALUE</text>
</package>
</packages>
<packages3d>
<package3d name="22-23-2041" urn="urn:adsk.eagle:package:8078635/1" type="box" library_version="5">
<description>&lt;b&gt;KK® 254 Solid Header, Vertical, with Friction Lock, 4 Circuits, Tin (Sn) Plating&lt;/b&gt;&lt;p&gt;&lt;a href =http://www.molex.com/pdm_docs/sd/022232041_sd.pdf&gt;Datasheet &lt;/a&gt;</description>
<packageinstances>
<packageinstance name="22-23-2041"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="MV" urn="urn:adsk.eagle:symbol:6783/2" library_version="5">
<wire x1="1.27" y1="0" x2="0" y2="0" width="0.6096" layer="94"/>
<text x="2.54" y="-0.762" size="1.524" layer="95">&gt;NAME</text>
<text x="-0.762" y="1.397" size="1.778" layer="96">&gt;VALUE</text>
<pin name="S" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
<symbol name="M" urn="urn:adsk.eagle:symbol:6785/2" library_version="5">
<wire x1="1.27" y1="0" x2="0" y2="0" width="0.6096" layer="94"/>
<text x="2.54" y="-0.762" size="1.524" layer="95">&gt;NAME</text>
<pin name="S" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="22-23-2041" urn="urn:adsk.eagle:component:8078936/3" prefix="X" library_version="5">
<description>.100" (2.54mm) Center Header - 4 Pin</description>
<gates>
<gate name="-1" symbol="MV" x="0" y="2.54" addlevel="always" swaplevel="1"/>
<gate name="-2" symbol="M" x="0" y="0" addlevel="always" swaplevel="1"/>
<gate name="-3" symbol="M" x="0" y="-2.54" addlevel="always" swaplevel="1"/>
<gate name="-4" symbol="M" x="0" y="-5.08" addlevel="always" swaplevel="1"/>
</gates>
<devices>
<device name="" package="22-23-2041">
<connects>
<connect gate="-1" pin="S" pad="1"/>
<connect gate="-2" pin="S" pad="2"/>
<connect gate="-3" pin="S" pad="3"/>
<connect gate="-4" pin="S" pad="4"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:8078635/1"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="MF" value="MOLEX" constant="no"/>
<attribute name="MPN" value="22-23-2041" constant="no"/>
<attribute name="OC_FARNELL" value="1462920" constant="no"/>
<attribute name="OC_NEWARK" value="38C0355" constant="no"/>
<attribute name="POPULARITY" value="21" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="JP1" library="pinhead" library_urn="urn:adsk.eagle:library:325" deviceset="PINHD-2X8" device="" package3d_urn="urn:adsk.eagle:package:22481/2"/>
<part name="JP2" library="pinhead" library_urn="urn:adsk.eagle:library:325" deviceset="PINHD-2X8" device="" package3d_urn="urn:adsk.eagle:package:22481/2"/>
<part name="JP3" library="pinhead" library_urn="urn:adsk.eagle:library:325" deviceset="PINHD-2X8" device="" package3d_urn="urn:adsk.eagle:package:22481/2"/>
<part name="JP4" library="pinhead" library_urn="urn:adsk.eagle:library:325" deviceset="PINHD-2X8" device="" package3d_urn="urn:adsk.eagle:package:22481/2"/>
<part name="JP5" library="pinhead" library_urn="urn:adsk.eagle:library:325" deviceset="PINHD-2X8" device="" package3d_urn="urn:adsk.eagle:package:22481/2"/>
<part name="JP6" library="pinhead" library_urn="urn:adsk.eagle:library:325" deviceset="PINHD-2X8" device="" package3d_urn="urn:adsk.eagle:package:22481/2"/>
<part name="JP7" library="pinhead" library_urn="urn:adsk.eagle:library:325" deviceset="PINHD-2X8" device="" package3d_urn="urn:adsk.eagle:package:22481/2"/>
<part name="JP8" library="pinhead" library_urn="urn:adsk.eagle:library:325" deviceset="PINHD-2X8" device="" package3d_urn="urn:adsk.eagle:package:22481/2"/>
<part name="P-1" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="-12V" device=""/>
<part name="P+1" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="+12V" device=""/>
<part name="P+2" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="+5V" device=""/>
<part name="GND1" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="P-2" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="-12V" device=""/>
<part name="P-3" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="-12V" device=""/>
<part name="P-4" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="-12V" device=""/>
<part name="P-5" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="-12V" device=""/>
<part name="P-6" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="-12V" device=""/>
<part name="P-7" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="-12V" device=""/>
<part name="P-8" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="-12V" device=""/>
<part name="P-9" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="-12V" device=""/>
<part name="P+3" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="+12V" device=""/>
<part name="P+4" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="+12V" device=""/>
<part name="P+5" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="+12V" device=""/>
<part name="P+6" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="+12V" device=""/>
<part name="P+7" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="+12V" device=""/>
<part name="P+8" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="+12V" device=""/>
<part name="P+9" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="+12V" device=""/>
<part name="P+10" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="+12V" device=""/>
<part name="GND2" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND3" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND4" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND5" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND6" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND7" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND8" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND9" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="P+11" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="+5V" device=""/>
<part name="P+12" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="+5V" device=""/>
<part name="P+13" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="+5V" device=""/>
<part name="P+14" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="+5V" device=""/>
<part name="P+15" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="+5V" device=""/>
<part name="P+16" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="+5V" device=""/>
<part name="P+17" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="+5V" device=""/>
<part name="X1" library="con-molex" library_urn="urn:adsk.eagle:library:165" deviceset="22-23-2041" device="" package3d_urn="urn:adsk.eagle:package:8078635/1"/>
<part name="P+18" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="+5V" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="JP1" gate="A" x="43.18" y="53.34" smashed="yes">
<attribute name="NAME" x="36.83" y="64.135" size="1.778" layer="95"/>
<attribute name="VALUE" x="36.83" y="38.1" size="1.778" layer="96"/>
</instance>
<instance part="JP2" gate="A" x="76.2" y="53.34" smashed="yes">
<attribute name="NAME" x="69.85" y="64.135" size="1.778" layer="95"/>
<attribute name="VALUE" x="69.85" y="38.1" size="1.778" layer="96"/>
</instance>
<instance part="JP3" gate="A" x="106.68" y="53.34" smashed="yes">
<attribute name="NAME" x="100.33" y="64.135" size="1.778" layer="95"/>
<attribute name="VALUE" x="100.33" y="38.1" size="1.778" layer="96"/>
</instance>
<instance part="JP4" gate="A" x="134.62" y="53.34" smashed="yes">
<attribute name="NAME" x="128.27" y="64.135" size="1.778" layer="95"/>
<attribute name="VALUE" x="128.27" y="38.1" size="1.778" layer="96"/>
</instance>
<instance part="JP5" gate="A" x="162.56" y="53.34" smashed="yes">
<attribute name="NAME" x="156.21" y="64.135" size="1.778" layer="95"/>
<attribute name="VALUE" x="156.21" y="38.1" size="1.778" layer="96"/>
</instance>
<instance part="JP6" gate="A" x="195.58" y="53.34" smashed="yes">
<attribute name="NAME" x="189.23" y="64.135" size="1.778" layer="95"/>
<attribute name="VALUE" x="189.23" y="38.1" size="1.778" layer="96"/>
</instance>
<instance part="JP7" gate="A" x="226.06" y="53.34" smashed="yes">
<attribute name="NAME" x="219.71" y="64.135" size="1.778" layer="95"/>
<attribute name="VALUE" x="219.71" y="38.1" size="1.778" layer="96"/>
</instance>
<instance part="JP8" gate="A" x="251.46" y="53.34" smashed="yes">
<attribute name="NAME" x="245.11" y="64.135" size="1.778" layer="95"/>
<attribute name="VALUE" x="245.11" y="38.1" size="1.778" layer="96"/>
</instance>
<instance part="P-1" gate="1" x="12.7" y="40.64" smashed="yes">
<attribute name="VALUE" x="10.16" y="38.1" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P+1" gate="1" x="7.62" y="53.34" smashed="yes">
<attribute name="VALUE" x="5.08" y="48.26" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P+2" gate="1" x="12.7" y="58.42" smashed="yes">
<attribute name="VALUE" x="10.16" y="53.34" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="GND1" gate="1" x="7.62" y="45.72" smashed="yes">
<attribute name="VALUE" x="5.08" y="43.18" size="1.778" layer="96"/>
</instance>
<instance part="P-2" gate="1" x="33.02" y="38.1" smashed="yes">
<attribute name="VALUE" x="30.48" y="35.56" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P-3" gate="1" x="66.04" y="38.1" smashed="yes">
<attribute name="VALUE" x="63.5" y="35.56" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P-4" gate="1" x="96.52" y="38.1" smashed="yes">
<attribute name="VALUE" x="93.98" y="35.56" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P-5" gate="1" x="124.46" y="38.1" smashed="yes">
<attribute name="VALUE" x="121.92" y="35.56" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P-6" gate="1" x="152.4" y="38.1" smashed="yes">
<attribute name="VALUE" x="149.86" y="35.56" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P-7" gate="1" x="185.42" y="38.1" smashed="yes">
<attribute name="VALUE" x="182.88" y="35.56" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P-8" gate="1" x="215.9" y="38.1" smashed="yes">
<attribute name="VALUE" x="213.36" y="35.56" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P-9" gate="1" x="241.3" y="38.1" smashed="yes">
<attribute name="VALUE" x="238.76" y="35.56" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P+3" gate="1" x="33.02" y="55.88" smashed="yes">
<attribute name="VALUE" x="30.48" y="50.8" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P+4" gate="1" x="66.04" y="55.88" smashed="yes">
<attribute name="VALUE" x="63.5" y="50.8" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P+5" gate="1" x="96.52" y="55.88" smashed="yes">
<attribute name="VALUE" x="93.98" y="50.8" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P+6" gate="1" x="124.46" y="55.88" smashed="yes">
<attribute name="VALUE" x="121.92" y="50.8" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P+7" gate="1" x="152.4" y="55.88" smashed="yes">
<attribute name="VALUE" x="149.86" y="50.8" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P+8" gate="1" x="185.42" y="55.88" smashed="yes">
<attribute name="VALUE" x="182.88" y="50.8" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P+9" gate="1" x="215.9" y="55.88" smashed="yes">
<attribute name="VALUE" x="213.36" y="50.8" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P+10" gate="1" x="241.3" y="55.88" smashed="yes">
<attribute name="VALUE" x="238.76" y="50.8" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="GND2" gate="1" x="33.02" y="45.72" smashed="yes">
<attribute name="VALUE" x="30.48" y="43.18" size="1.778" layer="96"/>
</instance>
<instance part="GND3" gate="1" x="66.04" y="45.72" smashed="yes">
<attribute name="VALUE" x="63.5" y="43.18" size="1.778" layer="96"/>
</instance>
<instance part="GND4" gate="1" x="96.52" y="45.72" smashed="yes">
<attribute name="VALUE" x="93.98" y="43.18" size="1.778" layer="96"/>
</instance>
<instance part="GND5" gate="1" x="124.46" y="45.72" smashed="yes">
<attribute name="VALUE" x="121.92" y="43.18" size="1.778" layer="96"/>
</instance>
<instance part="GND6" gate="1" x="152.4" y="45.72" smashed="yes">
<attribute name="VALUE" x="149.86" y="43.18" size="1.778" layer="96"/>
</instance>
<instance part="GND7" gate="1" x="185.42" y="45.72" smashed="yes">
<attribute name="VALUE" x="182.88" y="43.18" size="1.778" layer="96"/>
</instance>
<instance part="GND8" gate="1" x="215.9" y="45.72" smashed="yes">
<attribute name="VALUE" x="213.36" y="43.18" size="1.778" layer="96"/>
</instance>
<instance part="GND9" gate="1" x="241.3" y="45.72" smashed="yes">
<attribute name="VALUE" x="238.76" y="43.18" size="1.778" layer="96"/>
</instance>
<instance part="P+11" gate="1" x="55.88" y="58.42" smashed="yes">
<attribute name="VALUE" x="53.34" y="53.34" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P+12" gate="1" x="88.9" y="58.42" smashed="yes">
<attribute name="VALUE" x="86.36" y="53.34" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P+13" gate="1" x="119.38" y="58.42" smashed="yes">
<attribute name="VALUE" x="116.84" y="53.34" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P+14" gate="1" x="144.78" y="58.42" smashed="yes">
<attribute name="VALUE" x="142.24" y="53.34" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P+15" gate="1" x="175.26" y="58.42" smashed="yes">
<attribute name="VALUE" x="172.72" y="53.34" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P+16" gate="1" x="208.28" y="58.42" smashed="yes">
<attribute name="VALUE" x="205.74" y="53.34" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P+17" gate="1" x="238.76" y="58.42" smashed="yes">
<attribute name="VALUE" x="236.22" y="53.34" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="X1" gate="-1" x="15.24" y="53.34" smashed="yes">
<attribute name="NAME" x="17.78" y="52.578" size="1.524" layer="95"/>
<attribute name="VALUE" x="14.478" y="54.737" size="1.778" layer="96"/>
</instance>
<instance part="X1" gate="-2" x="15.24" y="50.8" smashed="yes">
<attribute name="NAME" x="17.78" y="50.038" size="1.524" layer="95"/>
</instance>
<instance part="X1" gate="-3" x="15.24" y="48.26" smashed="yes">
<attribute name="NAME" x="17.78" y="47.498" size="1.524" layer="95"/>
</instance>
<instance part="X1" gate="-4" x="15.24" y="45.72" smashed="yes">
<attribute name="NAME" x="17.78" y="44.958" size="1.524" layer="95"/>
</instance>
<instance part="P+18" gate="1" x="264.16" y="58.42" smashed="yes">
<attribute name="VALUE" x="261.62" y="53.34" size="1.778" layer="96" rot="R90"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="N$19" class="0">
<segment>
<pinref part="JP1" gate="A" pin="3"/>
<pinref part="JP1" gate="A" pin="4"/>
<wire x1="40.64" y1="58.42" x2="48.26" y2="58.42" width="0.1524" layer="91"/>
<pinref part="JP2" gate="A" pin="4"/>
<pinref part="JP2" gate="A" pin="3"/>
<wire x1="81.28" y1="58.42" x2="73.66" y2="58.42" width="0.1524" layer="91"/>
<wire x1="48.26" y1="58.42" x2="73.66" y2="58.42" width="0.1524" layer="91"/>
<junction x="48.26" y="58.42"/>
<junction x="73.66" y="58.42"/>
<pinref part="JP3" gate="A" pin="4"/>
<pinref part="JP3" gate="A" pin="3"/>
<wire x1="111.76" y1="58.42" x2="104.14" y2="58.42" width="0.1524" layer="91"/>
<wire x1="81.28" y1="58.42" x2="104.14" y2="58.42" width="0.1524" layer="91"/>
<junction x="81.28" y="58.42"/>
<junction x="104.14" y="58.42"/>
<pinref part="JP4" gate="A" pin="4"/>
<pinref part="JP4" gate="A" pin="3"/>
<wire x1="139.7" y1="58.42" x2="132.08" y2="58.42" width="0.1524" layer="91"/>
<wire x1="111.76" y1="58.42" x2="132.08" y2="58.42" width="0.1524" layer="91"/>
<junction x="111.76" y="58.42"/>
<junction x="132.08" y="58.42"/>
<pinref part="JP5" gate="A" pin="4"/>
<pinref part="JP5" gate="A" pin="3"/>
<wire x1="167.64" y1="58.42" x2="160.02" y2="58.42" width="0.1524" layer="91"/>
<wire x1="139.7" y1="58.42" x2="160.02" y2="58.42" width="0.1524" layer="91"/>
<junction x="139.7" y="58.42"/>
<junction x="160.02" y="58.42"/>
<pinref part="JP6" gate="A" pin="4"/>
<pinref part="JP6" gate="A" pin="3"/>
<wire x1="200.66" y1="58.42" x2="193.04" y2="58.42" width="0.1524" layer="91"/>
<wire x1="167.64" y1="58.42" x2="193.04" y2="58.42" width="0.1524" layer="91"/>
<junction x="167.64" y="58.42"/>
<junction x="193.04" y="58.42"/>
<pinref part="JP7" gate="A" pin="4"/>
<pinref part="JP7" gate="A" pin="3"/>
<wire x1="231.14" y1="58.42" x2="223.52" y2="58.42" width="0.1524" layer="91"/>
<wire x1="200.66" y1="58.42" x2="223.52" y2="58.42" width="0.1524" layer="91"/>
<junction x="200.66" y="58.42"/>
<junction x="223.52" y="58.42"/>
<pinref part="JP8" gate="A" pin="4"/>
<pinref part="JP8" gate="A" pin="3"/>
<wire x1="256.54" y1="58.42" x2="248.92" y2="58.42" width="0.1524" layer="91"/>
<wire x1="231.14" y1="58.42" x2="248.92" y2="58.42" width="0.1524" layer="91"/>
<junction x="231.14" y="58.42"/>
<junction x="248.92" y="58.42"/>
</segment>
</net>
<net name="N$45" class="0">
<segment>
<pinref part="JP8" gate="A" pin="1"/>
<pinref part="JP8" gate="A" pin="2"/>
<wire x1="248.92" y1="60.96" x2="256.54" y2="60.96" width="0.1524" layer="91"/>
<pinref part="JP7" gate="A" pin="1"/>
<pinref part="JP7" gate="A" pin="2"/>
<wire x1="223.52" y1="60.96" x2="231.14" y2="60.96" width="0.1524" layer="91"/>
<wire x1="248.92" y1="60.96" x2="231.14" y2="60.96" width="0.1524" layer="91"/>
<junction x="248.92" y="60.96"/>
<junction x="231.14" y="60.96"/>
<pinref part="JP6" gate="A" pin="1"/>
<pinref part="JP6" gate="A" pin="2"/>
<wire x1="193.04" y1="60.96" x2="200.66" y2="60.96" width="0.1524" layer="91"/>
<wire x1="223.52" y1="60.96" x2="200.66" y2="60.96" width="0.1524" layer="91"/>
<junction x="223.52" y="60.96"/>
<junction x="200.66" y="60.96"/>
<pinref part="JP5" gate="A" pin="1"/>
<pinref part="JP5" gate="A" pin="2"/>
<wire x1="160.02" y1="60.96" x2="167.64" y2="60.96" width="0.1524" layer="91"/>
<wire x1="193.04" y1="60.96" x2="167.64" y2="60.96" width="0.1524" layer="91"/>
<junction x="193.04" y="60.96"/>
<junction x="167.64" y="60.96"/>
<pinref part="JP4" gate="A" pin="1"/>
<pinref part="JP4" gate="A" pin="2"/>
<wire x1="132.08" y1="60.96" x2="139.7" y2="60.96" width="0.1524" layer="91"/>
<wire x1="160.02" y1="60.96" x2="139.7" y2="60.96" width="0.1524" layer="91"/>
<junction x="160.02" y="60.96"/>
<junction x="139.7" y="60.96"/>
<pinref part="JP3" gate="A" pin="1"/>
<pinref part="JP3" gate="A" pin="2"/>
<wire x1="104.14" y1="60.96" x2="111.76" y2="60.96" width="0.1524" layer="91"/>
<wire x1="132.08" y1="60.96" x2="111.76" y2="60.96" width="0.1524" layer="91"/>
<junction x="132.08" y="60.96"/>
<junction x="111.76" y="60.96"/>
<pinref part="JP2" gate="A" pin="1"/>
<pinref part="JP2" gate="A" pin="2"/>
<wire x1="73.66" y1="60.96" x2="81.28" y2="60.96" width="0.1524" layer="91"/>
<wire x1="104.14" y1="60.96" x2="81.28" y2="60.96" width="0.1524" layer="91"/>
<junction x="104.14" y="60.96"/>
<junction x="81.28" y="60.96"/>
<pinref part="JP1" gate="A" pin="2"/>
<pinref part="JP1" gate="A" pin="1"/>
<wire x1="48.26" y1="60.96" x2="40.64" y2="60.96" width="0.1524" layer="91"/>
<wire x1="73.66" y1="60.96" x2="48.26" y2="60.96" width="0.1524" layer="91"/>
<junction x="73.66" y="60.96"/>
<junction x="48.26" y="60.96"/>
</segment>
</net>
<net name="-12V" class="0">
<segment>
<pinref part="P-2" gate="1" pin="-12V"/>
<wire x1="33.02" y1="40.64" x2="33.02" y2="43.18" width="0.1524" layer="91"/>
<pinref part="JP1" gate="A" pin="15"/>
<pinref part="JP1" gate="A" pin="16"/>
<wire x1="40.64" y1="43.18" x2="48.26" y2="43.18" width="0.1524" layer="91"/>
<wire x1="33.02" y1="43.18" x2="40.64" y2="43.18" width="0.1524" layer="91"/>
<junction x="40.64" y="43.18"/>
</segment>
<segment>
<pinref part="P-3" gate="1" pin="-12V"/>
<wire x1="66.04" y1="40.64" x2="66.04" y2="43.18" width="0.1524" layer="91"/>
<pinref part="JP2" gate="A" pin="15"/>
<pinref part="JP2" gate="A" pin="16"/>
<wire x1="73.66" y1="43.18" x2="81.28" y2="43.18" width="0.1524" layer="91"/>
<wire x1="66.04" y1="43.18" x2="73.66" y2="43.18" width="0.1524" layer="91"/>
<junction x="73.66" y="43.18"/>
</segment>
<segment>
<pinref part="P-4" gate="1" pin="-12V"/>
<wire x1="96.52" y1="40.64" x2="96.52" y2="43.18" width="0.1524" layer="91"/>
<pinref part="JP3" gate="A" pin="15"/>
<pinref part="JP3" gate="A" pin="16"/>
<wire x1="104.14" y1="43.18" x2="111.76" y2="43.18" width="0.1524" layer="91"/>
<wire x1="96.52" y1="43.18" x2="104.14" y2="43.18" width="0.1524" layer="91"/>
<junction x="104.14" y="43.18"/>
</segment>
<segment>
<pinref part="P-5" gate="1" pin="-12V"/>
<wire x1="124.46" y1="40.64" x2="124.46" y2="43.18" width="0.1524" layer="91"/>
<pinref part="JP4" gate="A" pin="15"/>
<pinref part="JP4" gate="A" pin="16"/>
<wire x1="132.08" y1="43.18" x2="139.7" y2="43.18" width="0.1524" layer="91"/>
<wire x1="124.46" y1="43.18" x2="132.08" y2="43.18" width="0.1524" layer="91"/>
<junction x="132.08" y="43.18"/>
</segment>
<segment>
<pinref part="P-6" gate="1" pin="-12V"/>
<wire x1="152.4" y1="40.64" x2="152.4" y2="43.18" width="0.1524" layer="91"/>
<pinref part="JP5" gate="A" pin="15"/>
<pinref part="JP5" gate="A" pin="16"/>
<wire x1="160.02" y1="43.18" x2="167.64" y2="43.18" width="0.1524" layer="91"/>
<wire x1="152.4" y1="43.18" x2="160.02" y2="43.18" width="0.1524" layer="91"/>
<junction x="160.02" y="43.18"/>
</segment>
<segment>
<pinref part="P-7" gate="1" pin="-12V"/>
<wire x1="185.42" y1="40.64" x2="185.42" y2="43.18" width="0.1524" layer="91"/>
<pinref part="JP6" gate="A" pin="15"/>
<pinref part="JP6" gate="A" pin="16"/>
<wire x1="193.04" y1="43.18" x2="200.66" y2="43.18" width="0.1524" layer="91"/>
<wire x1="185.42" y1="43.18" x2="193.04" y2="43.18" width="0.1524" layer="91"/>
<junction x="193.04" y="43.18"/>
</segment>
<segment>
<pinref part="P-8" gate="1" pin="-12V"/>
<wire x1="215.9" y1="40.64" x2="215.9" y2="43.18" width="0.1524" layer="91"/>
<pinref part="JP7" gate="A" pin="15"/>
<pinref part="JP7" gate="A" pin="16"/>
<wire x1="223.52" y1="43.18" x2="231.14" y2="43.18" width="0.1524" layer="91"/>
<wire x1="215.9" y1="43.18" x2="223.52" y2="43.18" width="0.1524" layer="91"/>
<junction x="223.52" y="43.18"/>
</segment>
<segment>
<pinref part="P-9" gate="1" pin="-12V"/>
<wire x1="241.3" y1="40.64" x2="241.3" y2="43.18" width="0.1524" layer="91"/>
<pinref part="JP8" gate="A" pin="15"/>
<pinref part="JP8" gate="A" pin="16"/>
<wire x1="248.92" y1="43.18" x2="256.54" y2="43.18" width="0.1524" layer="91"/>
<wire x1="241.3" y1="43.18" x2="248.92" y2="43.18" width="0.1524" layer="91"/>
<junction x="248.92" y="43.18"/>
</segment>
<segment>
<pinref part="X1" gate="-4" pin="S"/>
<pinref part="P-1" gate="1" pin="-12V"/>
<wire x1="12.7" y1="45.72" x2="12.7" y2="43.18" width="0.1524" layer="91"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="JP1" gate="A" pin="14"/>
<pinref part="JP1" gate="A" pin="12"/>
<wire x1="48.26" y1="45.72" x2="48.26" y2="48.26" width="0.1524" layer="91"/>
<pinref part="JP1" gate="A" pin="10"/>
<wire x1="48.26" y1="48.26" x2="48.26" y2="50.8" width="0.1524" layer="91"/>
<junction x="48.26" y="48.26"/>
<pinref part="JP1" gate="A" pin="9"/>
<wire x1="48.26" y1="50.8" x2="40.64" y2="50.8" width="0.1524" layer="91"/>
<junction x="48.26" y="50.8"/>
<pinref part="JP1" gate="A" pin="11"/>
<wire x1="40.64" y1="50.8" x2="40.64" y2="48.26" width="0.1524" layer="91"/>
<junction x="40.64" y="50.8"/>
<pinref part="JP1" gate="A" pin="13"/>
<wire x1="40.64" y1="48.26" x2="40.64" y2="45.72" width="0.1524" layer="91"/>
<junction x="40.64" y="48.26"/>
<wire x1="40.64" y1="48.26" x2="48.26" y2="48.26" width="0.1524" layer="91"/>
<wire x1="48.26" y1="45.72" x2="40.64" y2="45.72" width="0.1524" layer="91"/>
<junction x="48.26" y="45.72"/>
<junction x="40.64" y="45.72"/>
<pinref part="GND2" gate="1" pin="GND"/>
<wire x1="33.02" y1="48.26" x2="40.64" y2="48.26" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="JP2" gate="A" pin="14"/>
<pinref part="JP2" gate="A" pin="12"/>
<wire x1="81.28" y1="45.72" x2="81.28" y2="48.26" width="0.1524" layer="91"/>
<pinref part="JP2" gate="A" pin="10"/>
<wire x1="81.28" y1="48.26" x2="81.28" y2="50.8" width="0.1524" layer="91"/>
<junction x="81.28" y="48.26"/>
<pinref part="JP2" gate="A" pin="9"/>
<wire x1="81.28" y1="50.8" x2="73.66" y2="50.8" width="0.1524" layer="91"/>
<junction x="81.28" y="50.8"/>
<pinref part="JP2" gate="A" pin="11"/>
<wire x1="73.66" y1="50.8" x2="73.66" y2="48.26" width="0.1524" layer="91"/>
<junction x="73.66" y="50.8"/>
<pinref part="JP2" gate="A" pin="13"/>
<wire x1="73.66" y1="48.26" x2="73.66" y2="45.72" width="0.1524" layer="91"/>
<junction x="73.66" y="48.26"/>
<wire x1="73.66" y1="45.72" x2="81.28" y2="45.72" width="0.1524" layer="91"/>
<junction x="73.66" y="45.72"/>
<junction x="81.28" y="45.72"/>
<wire x1="81.28" y1="48.26" x2="73.66" y2="48.26" width="0.1524" layer="91"/>
<pinref part="GND3" gate="1" pin="GND"/>
<wire x1="66.04" y1="48.26" x2="73.66" y2="48.26" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="JP3" gate="A" pin="14"/>
<pinref part="JP3" gate="A" pin="12"/>
<wire x1="111.76" y1="45.72" x2="111.76" y2="48.26" width="0.1524" layer="91"/>
<pinref part="JP3" gate="A" pin="10"/>
<wire x1="111.76" y1="48.26" x2="111.76" y2="50.8" width="0.1524" layer="91"/>
<junction x="111.76" y="48.26"/>
<pinref part="JP3" gate="A" pin="9"/>
<wire x1="111.76" y1="50.8" x2="104.14" y2="50.8" width="0.1524" layer="91"/>
<junction x="111.76" y="50.8"/>
<pinref part="JP3" gate="A" pin="11"/>
<wire x1="104.14" y1="50.8" x2="104.14" y2="48.26" width="0.1524" layer="91"/>
<junction x="104.14" y="50.8"/>
<pinref part="JP3" gate="A" pin="13"/>
<wire x1="104.14" y1="48.26" x2="104.14" y2="45.72" width="0.1524" layer="91"/>
<junction x="104.14" y="48.26"/>
<wire x1="104.14" y1="45.72" x2="111.76" y2="45.72" width="0.1524" layer="91"/>
<junction x="104.14" y="45.72"/>
<junction x="111.76" y="45.72"/>
<wire x1="111.76" y1="48.26" x2="104.14" y2="48.26" width="0.1524" layer="91"/>
<pinref part="GND4" gate="1" pin="GND"/>
<wire x1="104.14" y1="48.26" x2="96.52" y2="48.26" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="JP4" gate="A" pin="14"/>
<pinref part="JP4" gate="A" pin="12"/>
<wire x1="139.7" y1="45.72" x2="139.7" y2="48.26" width="0.1524" layer="91"/>
<pinref part="JP4" gate="A" pin="10"/>
<wire x1="139.7" y1="48.26" x2="139.7" y2="50.8" width="0.1524" layer="91"/>
<junction x="139.7" y="48.26"/>
<pinref part="JP4" gate="A" pin="9"/>
<wire x1="139.7" y1="50.8" x2="132.08" y2="50.8" width="0.1524" layer="91"/>
<junction x="139.7" y="50.8"/>
<pinref part="JP4" gate="A" pin="11"/>
<wire x1="132.08" y1="50.8" x2="132.08" y2="48.26" width="0.1524" layer="91"/>
<junction x="132.08" y="50.8"/>
<pinref part="JP4" gate="A" pin="13"/>
<wire x1="132.08" y1="48.26" x2="132.08" y2="45.72" width="0.1524" layer="91"/>
<junction x="132.08" y="48.26"/>
<wire x1="132.08" y1="48.26" x2="139.7" y2="48.26" width="0.1524" layer="91"/>
<wire x1="139.7" y1="45.72" x2="132.08" y2="45.72" width="0.1524" layer="91"/>
<junction x="139.7" y="45.72"/>
<junction x="132.08" y="45.72"/>
<pinref part="GND5" gate="1" pin="GND"/>
<wire x1="132.08" y1="48.26" x2="124.46" y2="48.26" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="JP5" gate="A" pin="14"/>
<pinref part="JP5" gate="A" pin="12"/>
<wire x1="167.64" y1="45.72" x2="167.64" y2="48.26" width="0.1524" layer="91"/>
<pinref part="JP5" gate="A" pin="10"/>
<wire x1="167.64" y1="48.26" x2="167.64" y2="50.8" width="0.1524" layer="91"/>
<junction x="167.64" y="48.26"/>
<pinref part="JP5" gate="A" pin="9"/>
<wire x1="167.64" y1="50.8" x2="160.02" y2="50.8" width="0.1524" layer="91"/>
<junction x="167.64" y="50.8"/>
<pinref part="JP5" gate="A" pin="11"/>
<wire x1="160.02" y1="50.8" x2="160.02" y2="48.26" width="0.1524" layer="91"/>
<junction x="160.02" y="50.8"/>
<pinref part="JP5" gate="A" pin="13"/>
<wire x1="160.02" y1="48.26" x2="160.02" y2="45.72" width="0.1524" layer="91"/>
<junction x="160.02" y="48.26"/>
<wire x1="160.02" y1="45.72" x2="167.64" y2="45.72" width="0.1524" layer="91"/>
<junction x="160.02" y="45.72"/>
<junction x="167.64" y="45.72"/>
<wire x1="167.64" y1="48.26" x2="160.02" y2="48.26" width="0.1524" layer="91"/>
<pinref part="GND6" gate="1" pin="GND"/>
<wire x1="152.4" y1="48.26" x2="160.02" y2="48.26" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="JP6" gate="A" pin="14"/>
<pinref part="JP6" gate="A" pin="12"/>
<wire x1="200.66" y1="45.72" x2="200.66" y2="48.26" width="0.1524" layer="91"/>
<pinref part="JP6" gate="A" pin="10"/>
<wire x1="200.66" y1="48.26" x2="200.66" y2="50.8" width="0.1524" layer="91"/>
<junction x="200.66" y="48.26"/>
<pinref part="JP6" gate="A" pin="9"/>
<wire x1="200.66" y1="50.8" x2="193.04" y2="50.8" width="0.1524" layer="91"/>
<junction x="200.66" y="50.8"/>
<pinref part="JP6" gate="A" pin="11"/>
<wire x1="193.04" y1="50.8" x2="193.04" y2="48.26" width="0.1524" layer="91"/>
<junction x="193.04" y="50.8"/>
<pinref part="JP6" gate="A" pin="13"/>
<wire x1="193.04" y1="48.26" x2="193.04" y2="45.72" width="0.1524" layer="91"/>
<junction x="193.04" y="48.26"/>
<wire x1="193.04" y1="45.72" x2="200.66" y2="45.72" width="0.1524" layer="91"/>
<junction x="193.04" y="45.72"/>
<junction x="200.66" y="45.72"/>
<wire x1="200.66" y1="48.26" x2="193.04" y2="48.26" width="0.1524" layer="91"/>
<pinref part="GND7" gate="1" pin="GND"/>
<wire x1="185.42" y1="48.26" x2="193.04" y2="48.26" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="JP7" gate="A" pin="14"/>
<pinref part="JP7" gate="A" pin="12"/>
<wire x1="231.14" y1="45.72" x2="231.14" y2="48.26" width="0.1524" layer="91"/>
<pinref part="JP7" gate="A" pin="10"/>
<wire x1="231.14" y1="48.26" x2="231.14" y2="50.8" width="0.1524" layer="91"/>
<junction x="231.14" y="48.26"/>
<pinref part="JP7" gate="A" pin="9"/>
<wire x1="231.14" y1="50.8" x2="223.52" y2="50.8" width="0.1524" layer="91"/>
<junction x="231.14" y="50.8"/>
<pinref part="JP7" gate="A" pin="11"/>
<wire x1="223.52" y1="48.26" x2="231.14" y2="48.26" width="0.1524" layer="91"/>
<wire x1="223.52" y1="50.8" x2="223.52" y2="48.26" width="0.1524" layer="91"/>
<junction x="223.52" y="50.8"/>
<junction x="223.52" y="48.26"/>
<pinref part="JP7" gate="A" pin="13"/>
<wire x1="223.52" y1="48.26" x2="223.52" y2="45.72" width="0.1524" layer="91"/>
<pinref part="GND8" gate="1" pin="GND"/>
<wire x1="215.9" y1="48.26" x2="223.52" y2="48.26" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="JP8" gate="A" pin="14"/>
<pinref part="JP8" gate="A" pin="12"/>
<wire x1="256.54" y1="45.72" x2="256.54" y2="48.26" width="0.1524" layer="91"/>
<pinref part="JP8" gate="A" pin="10"/>
<wire x1="256.54" y1="50.8" x2="256.54" y2="48.26" width="0.1524" layer="91"/>
<junction x="256.54" y="48.26"/>
<pinref part="JP8" gate="A" pin="9"/>
<wire x1="256.54" y1="50.8" x2="248.92" y2="50.8" width="0.1524" layer="91"/>
<junction x="256.54" y="50.8"/>
<pinref part="JP8" gate="A" pin="11"/>
<wire x1="248.92" y1="50.8" x2="248.92" y2="48.26" width="0.1524" layer="91"/>
<junction x="248.92" y="50.8"/>
<pinref part="JP8" gate="A" pin="13"/>
<wire x1="248.92" y1="48.26" x2="248.92" y2="45.72" width="0.1524" layer="91"/>
<junction x="248.92" y="48.26"/>
<wire x1="248.92" y1="48.26" x2="256.54" y2="48.26" width="0.1524" layer="91"/>
<wire x1="256.54" y1="45.72" x2="248.92" y2="45.72" width="0.1524" layer="91"/>
<junction x="256.54" y="45.72"/>
<junction x="248.92" y="45.72"/>
<pinref part="GND9" gate="1" pin="GND"/>
<wire x1="248.92" y1="48.26" x2="241.3" y2="48.26" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND1" gate="1" pin="GND"/>
<pinref part="X1" gate="-3" pin="S"/>
<wire x1="7.62" y1="48.26" x2="12.7" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="+12V" class="0">
<segment>
<pinref part="JP1" gate="A" pin="7"/>
<pinref part="JP1" gate="A" pin="8"/>
<wire x1="40.64" y1="53.34" x2="48.26" y2="53.34" width="0.1524" layer="91"/>
<pinref part="P+3" gate="1" pin="+12V"/>
<wire x1="40.64" y1="53.34" x2="33.02" y2="53.34" width="0.1524" layer="91"/>
<junction x="40.64" y="53.34"/>
</segment>
<segment>
<pinref part="JP2" gate="A" pin="8"/>
<pinref part="JP2" gate="A" pin="7"/>
<wire x1="81.28" y1="53.34" x2="73.66" y2="53.34" width="0.1524" layer="91"/>
<pinref part="P+4" gate="1" pin="+12V"/>
<wire x1="66.04" y1="53.34" x2="73.66" y2="53.34" width="0.1524" layer="91"/>
<junction x="73.66" y="53.34"/>
</segment>
<segment>
<pinref part="JP3" gate="A" pin="8"/>
<pinref part="JP3" gate="A" pin="7"/>
<wire x1="111.76" y1="53.34" x2="104.14" y2="53.34" width="0.1524" layer="91"/>
<pinref part="P+5" gate="1" pin="+12V"/>
<wire x1="96.52" y1="53.34" x2="104.14" y2="53.34" width="0.1524" layer="91"/>
<junction x="104.14" y="53.34"/>
</segment>
<segment>
<pinref part="JP4" gate="A" pin="8"/>
<pinref part="JP4" gate="A" pin="7"/>
<wire x1="139.7" y1="53.34" x2="132.08" y2="53.34" width="0.1524" layer="91"/>
<pinref part="P+6" gate="1" pin="+12V"/>
<wire x1="124.46" y1="53.34" x2="132.08" y2="53.34" width="0.1524" layer="91"/>
<junction x="132.08" y="53.34"/>
</segment>
<segment>
<pinref part="JP5" gate="A" pin="8"/>
<pinref part="JP5" gate="A" pin="7"/>
<wire x1="167.64" y1="53.34" x2="160.02" y2="53.34" width="0.1524" layer="91"/>
<pinref part="P+7" gate="1" pin="+12V"/>
<wire x1="152.4" y1="53.34" x2="160.02" y2="53.34" width="0.1524" layer="91"/>
<junction x="160.02" y="53.34"/>
</segment>
<segment>
<pinref part="JP6" gate="A" pin="8"/>
<pinref part="JP6" gate="A" pin="7"/>
<wire x1="200.66" y1="53.34" x2="193.04" y2="53.34" width="0.1524" layer="91"/>
<pinref part="P+8" gate="1" pin="+12V"/>
<wire x1="185.42" y1="53.34" x2="193.04" y2="53.34" width="0.1524" layer="91"/>
<junction x="193.04" y="53.34"/>
</segment>
<segment>
<pinref part="JP7" gate="A" pin="8"/>
<pinref part="JP7" gate="A" pin="7"/>
<wire x1="231.14" y1="53.34" x2="223.52" y2="53.34" width="0.1524" layer="91"/>
<pinref part="P+9" gate="1" pin="+12V"/>
<wire x1="215.9" y1="53.34" x2="223.52" y2="53.34" width="0.1524" layer="91"/>
<junction x="223.52" y="53.34"/>
</segment>
<segment>
<pinref part="JP8" gate="A" pin="8"/>
<pinref part="JP8" gate="A" pin="7"/>
<wire x1="256.54" y1="53.34" x2="248.92" y2="53.34" width="0.1524" layer="91"/>
<pinref part="P+10" gate="1" pin="+12V"/>
<wire x1="241.3" y1="53.34" x2="248.92" y2="53.34" width="0.1524" layer="91"/>
<junction x="248.92" y="53.34"/>
</segment>
<segment>
<pinref part="X1" gate="-2" pin="S"/>
<pinref part="P+1" gate="1" pin="+12V"/>
<wire x1="12.7" y1="50.8" x2="7.62" y2="50.8" width="0.1524" layer="91"/>
</segment>
</net>
<net name="+5V" class="0">
<segment>
<pinref part="JP1" gate="A" pin="6"/>
<pinref part="JP1" gate="A" pin="5"/>
<wire x1="48.26" y1="55.88" x2="40.64" y2="55.88" width="0.1524" layer="91"/>
<pinref part="P+11" gate="1" pin="+5V"/>
<wire x1="55.88" y1="55.88" x2="48.26" y2="55.88" width="0.1524" layer="91"/>
<junction x="48.26" y="55.88"/>
</segment>
<segment>
<pinref part="JP2" gate="A" pin="5"/>
<pinref part="JP2" gate="A" pin="6"/>
<wire x1="73.66" y1="55.88" x2="81.28" y2="55.88" width="0.1524" layer="91"/>
<pinref part="P+12" gate="1" pin="+5V"/>
<wire x1="88.9" y1="55.88" x2="81.28" y2="55.88" width="0.1524" layer="91"/>
<junction x="81.28" y="55.88"/>
</segment>
<segment>
<pinref part="JP3" gate="A" pin="5"/>
<pinref part="JP3" gate="A" pin="6"/>
<wire x1="104.14" y1="55.88" x2="111.76" y2="55.88" width="0.1524" layer="91"/>
<pinref part="P+13" gate="1" pin="+5V"/>
<wire x1="119.38" y1="55.88" x2="111.76" y2="55.88" width="0.1524" layer="91"/>
<junction x="111.76" y="55.88"/>
</segment>
<segment>
<pinref part="JP4" gate="A" pin="5"/>
<pinref part="JP4" gate="A" pin="6"/>
<wire x1="132.08" y1="55.88" x2="139.7" y2="55.88" width="0.1524" layer="91"/>
<pinref part="P+14" gate="1" pin="+5V"/>
<wire x1="139.7" y1="55.88" x2="144.78" y2="55.88" width="0.1524" layer="91"/>
<junction x="139.7" y="55.88"/>
</segment>
<segment>
<pinref part="JP5" gate="A" pin="5"/>
<pinref part="JP5" gate="A" pin="6"/>
<wire x1="160.02" y1="55.88" x2="167.64" y2="55.88" width="0.1524" layer="91"/>
<pinref part="P+15" gate="1" pin="+5V"/>
<wire x1="175.26" y1="55.88" x2="167.64" y2="55.88" width="0.1524" layer="91"/>
<junction x="167.64" y="55.88"/>
</segment>
<segment>
<pinref part="JP6" gate="A" pin="5"/>
<pinref part="JP6" gate="A" pin="6"/>
<wire x1="193.04" y1="55.88" x2="200.66" y2="55.88" width="0.1524" layer="91"/>
<pinref part="P+16" gate="1" pin="+5V"/>
<wire x1="200.66" y1="55.88" x2="208.28" y2="55.88" width="0.1524" layer="91"/>
<junction x="200.66" y="55.88"/>
</segment>
<segment>
<pinref part="JP7" gate="A" pin="5"/>
<pinref part="JP7" gate="A" pin="6"/>
<wire x1="223.52" y1="55.88" x2="231.14" y2="55.88" width="0.1524" layer="91"/>
<pinref part="P+17" gate="1" pin="+5V"/>
<wire x1="238.76" y1="55.88" x2="231.14" y2="55.88" width="0.1524" layer="91"/>
<junction x="231.14" y="55.88"/>
</segment>
<segment>
<pinref part="X1" gate="-1" pin="S"/>
<pinref part="P+2" gate="1" pin="+5V"/>
<wire x1="12.7" y1="53.34" x2="12.7" y2="55.88" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="JP8" gate="A" pin="5"/>
<pinref part="JP8" gate="A" pin="6"/>
<wire x1="248.92" y1="55.88" x2="256.54" y2="55.88" width="0.1524" layer="91"/>
<pinref part="P+18" gate="1" pin="+5V"/>
<wire x1="264.16" y1="55.88" x2="256.54" y2="55.88" width="0.1524" layer="91"/>
<junction x="256.54" y="55.88"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports the association of 3D packages
with devices in libraries, schematics, and board files. Those 3D
packages will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
