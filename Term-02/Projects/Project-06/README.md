<div align="center">

  <h1>📈 UTTrade - Stock Market Order Matching Engine</h1>
  <p><b>Advanced Programming (AP) Project | C++ Object-Oriented Stock Exchange Simulator</b></p>

  <p>
    <img src="https://img.shields.io/badge/Language-C%2B%2B20-blue.svg" alt="C++20">
    <img src="https://img.shields.io/badge/Architecture-Object--Oriented-orange.svg" alt="OOP Design">
    <img src="https://img.shields.io/badge/Build-Makefile-green.svg" alt="Makefile">
  </p>

</div>

---

<h2>📌 Overview & Introduction</h2>
<p>
<b>UTTrade</b> is an Object-Oriented C++ application designed to simulate a real-time Stock Exchange and Order Matching System[cite: 2]. The platform registers shareholders and companies, queues buy/sell limit orders, dynamically matches trades based on exact quantity and price criteria, locks/unlocks user funds and stock shares, updates spot prices, and generates detailed individual portfolio and company level reports[cite: 2].
</p>

---

<h2>🚀 Program Execution & Input Specifications</h2>

<p>The program is built using a multi-file architecture with C++20 standard and executed via CLI by passing paths to two CSV input files[cite: 2]:</p>

<pre>./UTTrade &lt;/path/to/companies.csv&gt; &lt;/path/to/shareholders.csv&gt;</pre>

<h3>1. Companies Data File (<code>companies.csv</code>)</h3>
<p>Contains initial company names and their starting share price[cite: 2]. No spaces allowed in company names[cite: 2].</p>
<pre>Name, Price
Foolad, 50
Khodro, 70
Petroshimi, 30
Nassaji, 45</pre>

<h3>2. Shareholders Data File (<code>shareholders.csv</code>)</h3>
<p>Contains shareholder usernames (no spaces), initial cash credit, and initial stock portfolio[cite: 2]. Portfolio format uses <code>Company:Count</code> separated by semicolons (<code>;</code>)[cite: 2].</p>
<pre>Username, Credit, Shares
Mehrab, 500, Foolad: 5
Daei, 100, Petroshimi:2; Foolad: 3; Khodro:1
Mahdiyar, 200, Nassaji:5; Petroshimi:3</pre>

---

<h2>⚙️ Core Matching Engine & Order Rules</h2>

<ul>
  <li><b>Global Order ID:</b> Each successfully created order receives a system-wide unique auto-incrementing ID starting from <code>1</code>[cite: 2]. Invalid orders due to errors receive no ID[cite: 2].</li>
  <li><b>Matching Criteria:</b> A buy order matches a sell order for the same company if and only if both <b>share count</b> AND <b>price per share</b> are exactly equal[cite: 2].</li>
  <li><b>Priority Tie-Breaking:</b> If multiple candidate orders match the criteria, the order with the <b>smallest Order ID</b> (earliest queued) is executed first[cite: 2].</li>
  <li><b>Spot Price Update:</b> Upon a successful trade match, the company's real-time market price updates immediately to the execution price[cite: 2].</li>
  <li><b>Locked Capital Mechanism:</b>
    <ul>
      <li><b>Sell Orders:</b> Shares in the order are locked from the seller's free shares[cite: 2].</li>
      <li><b>Buy Orders:</b> Total required cash (<code>count * price</code>) is locked from the buyer's free credit[cite: 2].</li>
    </ul>
  </li>
  <li><b>Opposing Queue Constraint:</b> A user cannot place a sell order if they already have an active buy order queued for that company, and vice-versa[cite: 2].</li>
</ul>

---

<h2>🕹️ Commands & CLI Specifications</h2>

<h3>1. Register Shareholder (<code>register</code>)</h3>
<p>Registers a new user with initial credit and an empty stock portfolio[cite: 2].</p>

<b>Input Format:</b>
<pre>register &lt;username&gt; &lt;credit&gt;</pre>

<b>Sample Outputs:</b>
<pre>Sadegh registered successfully.
Mehrab already exists.</pre>

<hr>

<h3>2. Place Sell Order (<code>sell_order</code>)</h3>
<p>Attempts to match with existing buy orders. If matched, transfers money and stock, and updates spot price[cite: 2]. Otherwise, locks shares and enqueues[cite: 2].</p>

<b>Input Format:</b>
<pre>sell_order &lt;username&gt; &lt;shares_count&gt; &lt;company&gt; &lt;share_price&gt;</pre>

<b>Sample Outputs:</b>
<pre>Order 2 matched with order 1.
Order 3 queued.
Insufficient free shares.
Sepanta already has a buy order queued for Khodro.</pre>

<hr>

<h3>3. Place Buy Order (<code>buy_order</code>)</h3>
<p>Attempts to match with existing sell orders[cite: 2]. If matched, transfers capital and stock[cite: 2]. Otherwise, locks credit and enqueues[cite: 2].</p>

<b>Input Format:</b>
<pre>buy_order &lt;username&gt; &lt;shares_count&gt; &lt;company&gt; &lt;share_price&gt;</pre>

<b>Sample Outputs:</b>
<pre>Order 7 matched with order 5.
Order 8 queued.
Insufficient free credit.
Kosar already has a sell order queued for Nassaji.</pre>

<hr>

<h3>4. Cancel Order (<code>cancel_order</code>)</h3>
<p>Removes an active order from its queue and unlocks the corresponding cash or shares[cite: 2].</p>

<b>Input Format:</b>
<pre>cancel_order &lt;id&gt;</pre>

<b>Sample Outputs:</b>
<pre>Canceled order 5.
Order 5 not found.</pre>

<hr>

<h3>5. User Portfolio Report (<code>report_portfolio</code>)</h3>
<p>Displays free/locked financial assets. Free shares are listed in ascending alphabetical order[cite: 2].</p>

<b>Input Format:</b>
<pre>report_portfolio &lt;username&gt;</pre>

<b>Sample Code Output:</b>
<pre>Mahdiyar Portfolio
Total free assets: $610
Free credit: $200
Locked credit: $500
Free shares:
1. Foolad: 4
2. Khodro: 3
Locked shares:
1. Foolad: 2</pre>

<hr>

<h3>6. Company Market Report (<code>report_company</code>)</h3>
<p>Displays spot price and current active order queues[cite: 2].</p>
<ul>
  <li><b>Sell Queue Sorting:</b> Lowest price first (ascending)[cite: 2]. Tie-breaker: Smallest ID[cite: 2].</li>
  <li><b>Buy Queue Sorting:</b> Highest price first (descending)[cite: 2]. Tie-breaker: Smallest ID[cite: 2].</li>
</ul>

<b>Input Format:</b>
<pre>report_company &lt;company&gt;</pre>

<b>Sample Code Output:</b>
<pre>Petroshimi report
Current price: $10
sell queue:
1. Shares: 4 Price: $13 ID: 2
2. Shares: 7 Price: $14 ID: 3
buy queue:
1. Shares: 5 Price: $10 ID: 8
2. Shares: 4 Price: $9 ID: 1</pre>

---

<h2>🧮 Asset Calculation Formulas</h2>

<details>
  <summary><b>Total Free Assets Formula</b></summary>
  <br>
  <code>Total Free Assets = Free Credit + SUM(Free Shares Count * Current Spot Price)</code>
  <p><i>Calculated dynamically using the latest spot price of each held stock[cite: 2].</i></p>
</details>

---

<h2>🛠️ Compilation & Multi-File Setup</h2>

<p>The project must be compiled using <code>make</code> with <b>C++20</b> support[cite: 2]. The generated binary must be named <code>UTTrade</code> in the root directory[cite: 2].</p>

<b>Build Commands:</b>
<pre>make
./UTTrade ./companies.csv ./shareholders.csv</pre>

---
