// https://observablehq.com/@d3/line-chart@183
export default function define(runtime, observer) {
  const main = runtime.module();
  const fileAttachments = new Map([["aapl.csv",new URL("./files/de259092d525c13bd10926eaf7add45b15f2771a8b39bc541a5bba1e0206add4880eb1d876be8df469328a85243b7d813a91feb8cc4966de582dc02e5f8609b7",import.meta.url)]]);
  main.builtin("FileAttachment", runtime.fileAttachments(name => fileAttachments.get(name)));
  main.variable(observer()).define(["md"], function(md){return(
md`# Line Chart

This static time series line chart shows the daily close of Apple stock. Compare to a [log *y*-scale showing change](/@d3/change-line-chart), an [area chart](/@d3/area-chart), a [horizon chart](/@d3/horizon-chart-ii), a [candlestick chart](/@d3/candlestick-chart), and an [index chart](/@d3/index-chart). To inspect values, consider a [tooltip](/@d3/line-chart-with-tooltip).

Data: [Yahoo Finance](https://finance.yahoo.com/lookup)`
)});
  main.variable(observer("chart")).define("chart", ["d3","width","height","xAxis","yAxis","data","line"], function(d3,width,height,xAxis,yAxis,data,line)
{
  const svg = d3.create("svg")
      .attr("viewBox", [0, 0, width, height]);

  svg.append("g")
      .call(xAxis);

  svg.append("g")
      .call(yAxis);

  svg.append("path")
      .datum(data)
      .attr("fill", "none")
      .attr("stroke", "steelblue")
      .attr("stroke-width", 1.5)
      .attr("stroke-linejoin", "round")
      .attr("stroke-linecap", "round")
      .attr("d", line);

  return svg.node();
}
);
  main.variable(observer("data")).define("data", ["d3","FileAttachment"], async function(d3,FileAttachment){return(
Object.assign((d3.csvParse(await FileAttachment("aapl.csv").text(), d3.autoType)).map(({date, close}) => ({date, value: close})), {y: "$ Close"})
)});
  main.variable(observer("line")).define("line", ["d3","x","y"], function(d3,x,y){return(
d3.line()
    .defined(d => !isNaN(d.value))
    .x(d => x(d.date))
    .y(d => y(d.value))
)});
  main.variable(observer("x")).define("x", ["d3","data","margin","width"], function(d3,data,margin,width){return(
d3.scaleUtc()
    .domain(d3.extent(data, d => d.date))
    .range([margin.left, width - margin.right])
)});
  main.variable(observer("y")).define("y", ["d3","data","height","margin"], function(d3,data,height,margin){return(
d3.scaleLinear()
    .domain([0, d3.max(data, d => d.value)]).nice()
    .range([height - margin.bottom, margin.top])
)});
  main.variable(observer("xAxis")).define("xAxis", ["height","margin","d3","x","width"], function(height,margin,d3,x,width){return(
g => g
    .attr("transform", `translate(0,${height - margin.bottom})`)
    .call(d3.axisBottom(x).ticks(width / 80).tickSizeOuter(0))
)});
  main.variable(observer("yAxis")).define("yAxis", ["margin","d3","y","data"], function(margin,d3,y,data){return(
g => g
    .attr("transform", `translate(${margin.left},0)`)
    .call(d3.axisLeft(y))
    .call(g => g.select(".domain").remove())
    .call(g => g.select(".tick:last-of-type text").clone()
        .attr("x", 3)
        .attr("text-anchor", "start")
        .attr("font-weight", "bold")
        .text(data.y))
)});
  main.variable(observer("margin")).define("margin", function(){return(
{top: 20, right: 30, bottom: 30, left: 40}
)});
  main.variable(observer("height")).define("height", function(){return(
500
)});
  main.variable(observer("d3")).define("d3", ["require"], function(require){return(
require("d3@5")
)});
  return main;
}
