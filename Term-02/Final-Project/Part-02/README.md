<div align="center">

  <h1>🏆 UTGame Phase 2 - Ranked Duels & Moderation System</h1>
  <p><b>Advanced Programming (AP) Assignment #5 (Phase 2) | C++ Ranked Matchmaking & Moderation Engine</b></p>

  <p>
    <img src="https://img.shields.io/badge/Language-C%2B%2B20-blue.svg" alt="C++20">
    <img src="https://img.shields.io/badge/Architecture-Object--Oriented-orange.svg" alt="OOP Architecture">
    <img src="https://img.shields.io/badge/Build-Makefile-green.svg" alt="Makefile">
  </p>

</div>

---

<h2>📌 Overview & Introduction</h2>
<p>
<b>UTGame Phase 2</b> expands upon the Phase 1 online gaming platform by introducing competitive <b>Ranked Matches</b>, tier-based player levels (Bronze, Silver, Golden, Platinum), Ranked Points (RP) mechanics, player blocking capabilities, and advanced administrative moderation tools to penalize reported players[cite: 4].
</p>

---

<h2>🚀 Execution & Configuration Updates</h2>

<p>The program execution command remains identical to Phase 1[cite: 4]:</p>

<pre>./UTGame &lt;/path/to/players.csv&gt; &lt;/path/to/admins.csv&gt;</pre>

<h3>1. Updated Players File Format (<code>players.csv</code>)</h3>
<p>The CSV now includes an extra fourth column for initial <b>Ranked Points (RP)</b>[cite: 4]. Newly registered users start with default <code>1200 RP</code>[cite: 4].</p>

<pre>username, password, XP, RP
pishikoochool, meooow, 1500, 2350
amir, italy, 900, 1600
iliya, ghasab, 1300, 1200</pre>

---

<h2>⚙️ New Systems & Mechanics</h2>

<h3>1. Player Tier Levels</h3>
<p>Players are classified into four distinct tiers based on their current <b>RP</b>[cite: 4]:</p>
<ul>
  <li><b>Bronze:</b> $RP \le 1400$[cite: 4]</li>
  <li><b>Silver:</b> $1400 < RP \le 1750$[cite: 4]</li>
  <li><b>Golden:</b> $1750 < RP \le 2250$[cite: 4]</li>
  <li><b>Platinum:</b> $RP > 2250$[cite: 4]</li>
</ul>

<h3>2. Ranked Match Rules</h3>
<ul>
  <li><b>Level Mismatch Enforcement:</b> Ranked matches can ONLY be started between players belonging to the same tier[cite: 4]. If tiers diverge by the time a match starts, starting the match fails with a <code>Level Mismatch</code> error and the invitation is deleted[cite: 4].</li>
  <li><b>Base Conditions:</b> Both players start a ranked match with <b>3 Bullets</b> and <b>3 Health Units</b>[cite: 4].</li>
  <li><b>Health Calculation:</b> Taking an unblocked shot reduces health by 1[cite: 4]. Reaching 0 health results in defeat[cite: 4].</li>
</ul>

<h3>3. Ranked Points (RP) Post-Match Calculation</h3>
<p>Upon concluding a ranked match, RP is recalculated as follows[cite: 4]:</p>

$$RP_{new, winner} = RP_{old} + \Delta RP + HealthBonus$$
$$RP_{new, loser} = RP_{old} - \Delta RP$$

<ul>
  <li><b>Tier Base Shift ($\Delta RP$):</b>
    <ul>
      <li>Bronze Tier: $\Delta RP = 75$[cite: 4]</li>
      <li>Silver Tier: $\Delta RP = 100$[cite: 4]</li>
      <li>Golden Tier: $\Delta RP = 125$[cite: 4]</li>
      <li>Platinum Tier: $\Delta RP = 150$[cite: 4]</li>
    </ul>
  </li>
  <li><b>Health Bonus:</b> $HealthBonus = RemainingHealth \times 25$[cite: 4]</li>
</ul>

<h3>4. Admin Penalty System</h3>
<p>Admins can resolve player reports by applying penalties that directly reduce starting health or bullets for a specified number of future ranked matches[cite: 4]:</p>
<ul>
  <li><b>Health Penalty Range:</b> $1 \le HealthPenalty \le 2$[cite: 4]</li>
  <li><b>Bullet Penalty Range:</b> $1 \le BulletPenalty \le 3$[cite: 4]</li>
  <li><b>Number of Matches Range:</b> $1 \le NumberOfMatches$[cite: 4]</li>
  <li><b>Penalty Behavior:</b> Applying a new penalty of the <i>same type</i> replaces the previous active penalty[cite: 4]. Applying a penalty of a <i>different type</i> stack together simultaneously[cite: 4]. Active matches are unaffected; penalties take effect starting from the subsequent match[cite: 4].</li>
</ul>

---

<h2>🕹️ New & Modified Commands Specification</h2>

<h3>1. Find Ranked Opponents (<code>GET ranked_match_opponents</code>)</h3>
<p>Lists available players in the exact same level tier sorted by RP[cite: 4]. Excludes the logged-in player[cite: 4]. Default sorting order is descending[cite: 4].</p>

<b>Input Format:</b>
<pre>GET ranked_match_opponents ? sort_order "&lt;asc|desc&gt;"</pre>

<b>Sample Output:</b>
<pre>1. iliya with 1200 RP
2. pishi with 720 RP</pre>

<hr>

<h3>2. Send Invitation (<code>POST invitation</code> - Updated)</h3>
<p>Supports <code>match_type "ranked"</code> in addition to <code>casual</code>[cite: 4]. Rejects invitation with <code>Not Found</code> error if the receiver has blocked the sender[cite: 4].</p>

<b>Input Format:</b>
<pre>POST invitation ? username "&lt;username&gt;" match_type "casual | ranked"</pre>

<b>Outputs:</b> <code>OK</code> | <code>Permission Denied</code> | <code>Bad Request</code> | <code>Not Found</code>[cite: 4]

<hr>

<h3>3. Block / Unblock Player (<code>POST block</code>)</h3>
<p>Blocks or unblocks a target player from sending invitations[cite: 4].</p>

<b>Input Format:</b>
<pre>POST block ? username "&lt;username&gt;" status "&lt;blocked|unblocked&gt;"</pre>

<b>Outputs:</b> <code>OK</code> | <code>Permission Denied</code> | <code>Bad Request</code> | <code>Not Found</code>[cite: 4]

<hr>

<h3>4. Apply Admin Penalty (<code>POST penalty</code> - Admin Only)</h3>
<p>Resolves a violation report by applying starting attribute penalties to the reported player and closes the report[cite: 4].</p>

<b>Input Format:</b>
<pre>POST penalty ? report_id "&lt;id&gt;" type "&lt;health_penalty|bullet_penalty&gt;" amount "&lt;amount&gt;" number_of_matches "&lt;count&gt;"</pre>

<b>Outputs:</b> <code>OK</code> | <code>Permission Denied</code> | <code>Bad Request</code> | <code>Not Found</code>[cite: 4]

<hr>

<h3>5. Dismiss Report (<code>POST dismiss_report</code> - Admin Only)</h3>
<p>Dismisses a violation report without applying penalties and removes it from the queue[cite: 4].</p>

<b>Input Format:</b>
<pre>POST dismiss_report ? report_id "&lt;report_id&gt;"</pre>

<b>Outputs:</b> <code>OK</code> | <code>Permission Denied</code> | <code>Bad Request</code> | <code>Not Found</code>[cite: 4]

<hr>

<h3>6. View Profile (<code>GET profile</code> - Updated)</h3>
<p>Now displays <b>Level Tier</b> and <b>RP</b> in addition to XP, Wins, and Losses[cite: 4].</p>

<b>Input Format:</b>
<pre>GET profile ? username "&lt;username&gt;"</pre>

<b>Sample Output:</b>
<pre>username: "iliya"
Level: Silver
RP: 1500
XP: 500
Total wins: 5
Total losses: 5</pre>

<hr>

<h3>7. View Match Status (<code>GET match_status</code> - Updated)</h3>
<p>Includes <code>Your remaining health</code> line when in an active Ranked Match[cite: 4].</p>

<b>Input Format:</b>
<pre>GET match_status ?</pre>

<b>Sample Output:</b>
<pre>Turn 1
You: shoot
Your opponent: pending
History:
Opponent's moves:   Your moves:
Your remaining bullets: 3
Your remaining health: 3</pre>

---

<h2>🛠️ Compilation & Build Instructions</h2>

<p>Must be compiled with <b>C++20</b> standard using standard multi-file architecture and a root-level <code>Makefile</code>[cite: 4].</p>

<b>Build Commands:</b>
<pre>make
./UTGame ./players.csv ./admins.csv</pre>

---
