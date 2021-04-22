import * as d3 from "d3";

var margin = { top: 30, right: 30, bottom: 85, left: 85 };
var width = 400;
var height = 400;

var svg = d3.select("#dataid")
    .append("svg")
    // .style("background-color", "red")
    .attr("width", width + margin.left + margin.right)
    .attr("height", height + margin.top + margin.bottom)
    .append("g")
    .attr("transform", `translate(${margin.left}, ${margin.top})`)

// X axis
var x = d3.scaleLinear()
    .domain([0, 4e3])
    .range([0, width])
    .nice()

// X axis label
svg.append("text")
    .attr("text-anchor", "end")
    .attr("x", width / 2 + margin.left)
    .attr("y", height + margin.top + 20)
    .text("Sepal Length");

svg.append("g")
    .attr("transform", `translate(0, ${height})`)
    .call(d3.axisBottom(x))

// Y axis
var y = d3.scaleLinear()
    .domain([0, 500e3])
    .range([height, 0])
    .nice()

// Y axis label
svg.append("text")
    .attr("text-anchor", "end")
    .attr("transform", "rotate(-90)")
    .attr("y", -margin.left + 20)
    .attr("x", -margin.top - height / 2 + 20)
    .text("Sale Price")

svg.append("g")
    .call(d3.axisLeft(y))


// var color = d3.scaleOrdinal()
//     .domain(["setosa", "versicolor", "virginica"])
//     .range(["#F8766D", "#00BA38", "#619CFF"])

const url = "https://raw.githubusercontent.com/holtzy/data_to_viz/master/Example_dataset/2_TwoNum.csv";
// d3.csv(url, function (data) {
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
        .style("fill", function (d) {
            if (d.SalePrice < 150e3) {
                return "green";
            } else if (d.SalePrice >= 150e3 && d.SalePrice < 300e3) {
                return "orange";
            } else if (d.SalePrice >= 300e3) {
                return "red";
            }
        })
})
