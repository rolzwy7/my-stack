import * as d3 from "d3";

var margin = { top: 30, right: 30, bottom: 30, left: 30 };
var width = 400;
var height = 400;

var svg = d3.select("#dataid")
    .append("svg")
    // .style("background-color", "red")
    .attr("width", width + margin.left + margin.right)
    .attr("height", height + margin.top + margin.bottom)
    .append("g")
    .attr("transform", `translate(${margin.left}, ${margin.top})`)

var x = d3.scaleLinear()
    .domain([0, 100]) // This is the min and the max of the data: 0 to 100 if percentages
    .range([0, width]); // This is the corresponding value I want in Pixel
// Try console.log( x(25) ) to see what this x function does.
// Answer: it translates 25 to 100 (25% of 400)
console.log(x(25));

svg
    .append("g")
    .attr("transform", `translate(0, ${height})`)
    .call(d3.axisBottom(x));

var y = d3.scaleLinear()
    .domain([0, 100])
    .range([height, 0])

svg
    .append("g")
    .call(d3.axisLeft(y));


var data = [{ x: 10, y: 20 }, { x: 40, y: 90 }, { x: 80, y: 50 }]

svg
    .selectAll("whatever") // selecting non existent things. weird i know
    .data(data)
    .enter() // Easy to forget !
    .append("circle")
    .attr("cx", (d) => x(d.x))
    .attr("cy", (d) => y(d.y))
    .attr("r", 7)