import * as d3 from "d3";

var margin = { top: 30, right: 30, bottom: 30, left: 50 };
var width = 400;
var height = 400;

var svg = d3.select("#dataid")
    .append("svg")
    // .style("background-color", "red")
    .attr("width", width + margin.left + margin.right)
    .attr("height", height + margin.top + margin.bottom)
    .append("g")
    .attr("transform", `translate(${margin.left}, ${margin.top})`)

// X
var x = d3.scaleLinear()
    .domain([0, 4e3])
    .range([0, width]);

svg.append("g")
    .attr("transform", `translate(0, ${height})`)
    .call(d3.axisBottom(x));

// Y
var y = d3.scaleLinear()
    .domain([0, 500e3])
    .range([height, 0])

svg.append("g")
    .call(d3.axisLeft(y));


const url = "https://raw.githubusercontent.com/holtzy/data_to_viz/master/Example_dataset/2_TwoNum.csv";
// d3.csv(url, function (data) { // For some reason this doesnt work
//     // console.log(data.GrLivArea);
//     document.querySelector("#seq").appendChild(document.createTextNode(data.GrLivArea))
//     svg.append("g")
//         .selectAll("dot")
//         .data(data)
//         .enter()
//         .append("circle")
//         .attr("cx", (d) => x(d.GrLivArea))
//         .attr("cy", (d) => y(d.SalePrice))
//         .attr("r", 5)
//         .style("fill", "#69b3a2")
// })
d3.csv(url).then(function (data) {
    svg.append("g")
        .selectAll("dot")
        .data(data)
        .enter()
        .append("circle")
        .attr("cx", (d) => x(d.GrLivArea))
        .attr("cy", (d) => y(d.SalePrice))
        .attr("r", 1.7)
        .style("fill", "#69b3a2")
})
