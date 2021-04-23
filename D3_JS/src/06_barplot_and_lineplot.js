import * as d3 from "d3";

// set the dimensions and margins of the graph
var margin = { top: 30, right: 30, bottom: 70, left: 60 },
    width = 460 - margin.left - margin.right,
    height = 400 - margin.top - margin.bottom;

// append the svg object to the body of the page
var svg = d3.select("#dataid")
    .append("svg")
    .attr("width", width + margin.left + margin.right)
    .attr("height", height + margin.top + margin.bottom)
    .append("g")
    .attr("transform",
        "translate(" + margin.left + "," + margin.top + ")");


d3.csv("https://raw.githubusercontent.com/holtzy/data_to_viz/master/Example_dataset/7_OneCatOneNum_header.csv").then(function (data) {
    // X axis
    var x = d3.scaleBand()
        .domain(data.map(function (d) { return d.Country; }))
        .range([0, width])
        .padding(0.2);

    svg.append("g")
        .attr("transform", `translate(0, ${height})`)
        .call(d3.axisBottom(x))
        .selectAll("text")
        .attr("transform", "translate(-10,0) rotate(-45)")
        .style("text-anchor", "end");

    // Add Y axis
    var y = d3.scaleLinear()
        .domain([0, 13000])
        .range([height, 0]);
    svg.append("g")
        .call(d3.axisLeft(y));

    svg.selectAll("mybar")
        .data(data)
        .enter()
        .append("rect")
        .attr("x", function (d) { return x(d.Country); })
        .attr("y", function (d) { return y(d.Value); })
        .attr("width", x.bandwidth())
        .attr("height", function (d) { return height - y(d.Value); })
        .attr("fill", "pink")
    var linedata = [
        { "Country": "United States", "Value": 12394 },
        { "Country": "Russia", "Value": 6148 },
        { "Country": "Germany (FRG)", "Value": 1653 },
        { "Country": "France", "Value": 2162 },
        { "Country": "United Kingdom", "Value": 1214 },
        { "Country": "China", "Value": 1131 },
        { "Country": "Spain", "Value": 814 },
        { "Country": "Netherlands", "Value": 1167 },
        { "Country": "Italy", "Value": 660 },
        { "Country": "Israel", "Value": 1263 },
    ]

    svg.append("path")
        .datum(linedata)
        .attr("fill", "none")
        .attr("stroke", "dodgerblue")
        .attr("stroke-width", 1.5)
        .attr("d", d3.line()
            .x(function (d) { return x(d.Country) + x.bandwidth() / 2 })
            .y(function (d) { return y(d.Value / 2) })
        )

})


