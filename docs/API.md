# API Reference

## Axes Methods

| Method | Description |
|--------|-------------|
| `plot(config)` | Line plot |
| `scatter(config)` | Scatter plot |
| `step(config)` | Step plot |
| `errorbar(config)` | Error bar plot |
| `loglog(config)` | Log-log plot |
| `semilogx(config)` | Semi-log x plot |
| `semilogy(config)` | Semi-log y plot |
| `fill(config)` | Filled polygon |
| `fill_between(config)` | Fill between two curves |
| `fill_betweenx(config)` | Fill between two curves (horizontal) |
| `bar_label(bars, labels)` | Bar labels |
| `twinx()` | Twin x-axis |
| `twiny()` | Twin y-axis |
| `legend(config)` | Legend |
| `grid(config)` | Grid |
| `tick_params(config)` | Tick parameters |
| `set_title(title)` | Set axes title |
| `set_xlabel(config)` | Set x label |
| `set_ylabel(config)` | Set y label |
| `set_xlim(config)` | Set x limits |
| `set_ylim(config)` | Set y limits |
| `get_xlim()` | Get x limits |
| `get_ylim()` | Get y limits |

---

## Figure Methods

| Method | Description |
|--------|-------------|
| `suptitle(title)` | Set figure title |
| `save(filename, dpi)` | Save figure to file |
| `tight_layout()` | Adjust subplot spacing |
| `clf()` | Clear figure |

---

## Pyplot Methods

| Method | Description |
|--------|-------------|
| `show(block)` | Display plots |
| `plot(config)` | Plot on current axes |
| `figure(config)` | Create new figure |
| `subplots(config)` | Create subplots |
| `subplot(nrows, ncols, num)` | Select subplot |
| `subplot2grid(config)` | Create subplot at grid location |
| `tight_layout()` | Adjust layout |
| `clf()` | Clear figure |
| `cla()` | Clear axes |
| `close()` | Close current figure |
| `close(string)` | Close figure by name |
| `close(int)` | Close figure by number |
| `title(t)` | Set title |
| `grid(config)` | Toggle grid |
| `sca(ax)` | Set current axes |
| `gca()` | Get current axes |
| `gcf()` | Get current figure |
| `get_fignums()` | Get open figure numbers |
| `get_figlabels()` | Get open figure labels |
| `fignum_exists(num)` | Check if figure exists |
| `axes(ax)` | Get axes |
| `delaxes(ax)` | Delete axes |
| `step(config)` | Step plot |
| `tick_params(config)` | Tick parameters |
| `legend(config)` | Legend |

---

## Configuration Structs

| Struct | Used by |
|--------|---------|
| `FigureConfig` | `Pyplot::figure()` |
| `SubplotsConfig` | `Pyplot::subplots()` |
| `subplot2gridConfig` | `Pyplot::subplot2grid()` |
| `PlotConfig` | `Axes::plot()`, `Pyplot::plot()` |
| `ScatterConfig` | `Axes::scatter()` |
| `StepConfig` | `Axes::step()` |
| `ErrorbarConfig` | `Axes::errorbar()` |
| `LogLogConfig` | `Axes::loglog()` |
| `SemiLogxConfig` | `Axes::semilogx()` |
| `SemiLogyConfig` | `Axes::semilogy()` |
| `FillConfig` | `Axes::fill()` |
| `FillBetweenConfig` | `Axes::fill_between()` |
| `FillBetweenxConfig` | `Axes::fill_betweenx()` |
| `GridConfig` | `Axes::grid()` |
| `LegendConfig` | `Axes::legend()` |
| `TickParamsConfig` | `Axes::tick_params()` |
| `XLabelConfig` | `Axes::set_xlabel()` |
| `YLabelConfig` | `Axes::set_ylabel()` |
| `SetXlimConfig` | `Axes::set_xlim()` |
| `SetYlimConfig` | `Axes::set_ylim()` |

---

## Type Aliases

| Type | Definition | Used for |
|------|-----------|---------|
| `Vec` | `std::vector<double>` with operators | x, y data with numpy-like ops |
| `DataValue` | `variant<double, vector<double>>` | x, y in errorbar |
| `ErrorValue` | `variant<double, vector<double>, vector<vector<double>>>` | xerr, yerr |
| `LimValue` | `variant<bool, vector<bool>>` | lolims, uplims |
| `ErrorEveryValue` | `variant<int, pair<int,int>>` | errorevery |
| `SizeValue` | `variant<double, Vec>` | scatter s |
| `ColorValue` | `variant<string, Vec>` | scatter c |
| `LinewidthsValue` | `variant<double, Vec>` | scatter linewidths |

---

## Enums

| Enum | Values | Used in |
|------|--------|---------|
| `Axis` | `X, Y, Both` | `TickParamsConfig`, `GridConfig` |
| `Which` | `Major, Minor, Both` | `TickParamsConfig`, `GridConfig` |
| `Direction` | `In, Out, InOut` | `TickParamsConfig` |
| `Loc` | `Bottom, Top, Center` | `XLabelConfig`, `YLabelConfig` |
| `Where` | `Pre, Post, Mid` | `StepConfig` |
| `NonPositive` | `Mask, Clip` | `LogLogConfig`, `SemiLogxConfig`, `SemiLogyConfig` |
| `Step` | `Pre, Post, Mid` | `FillBetweenConfig`, `FillBetweenxConfig` |

---

## NumpyUtils Helpers

| Function | Description |
|----------|-------------|
| `toNumpy<T>(vector<T>)` | Convert vector to numpy array |
| `toBoolArray(vector<bool>)` | Convert bool vector to numpy bool array |
| `toStringList(vector<string>)` | Convert string vector to Python list |
| `toSubs(vector<double>)` | Convert to Python tuple for subs parameter |
| `dataValueToNumpy(DataValue)` | Convert DataValue to numpy array |
| `errorValueToNumpy(ErrorValue)` | Convert ErrorValue to numpy array |
| `limValueToPython(LimValue)` | Convert LimValue to Python object |
| `colorValueToPython(ColorValue)` | Convert ColorValue to Python object |
| `sizeInPointsValueToPython(SizeValue)` | Convert SizeValue to Python object |
| `linewidthsToPython(LinewidthsValue)` | Convert LinewidthsValue to Python object |
