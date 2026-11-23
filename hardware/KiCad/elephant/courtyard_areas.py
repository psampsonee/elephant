import pcbnew
import csv
import os

board = pcbnew.GetBoard()
rows = []
scale = pcbnew.FromMils(1) ** 2

for fp in board.GetFootprints():
    layer = pcbnew.B_CrtYd if fp.IsFlipped() else pcbnew.F_CrtYd
    cy = fp.GetCourtyard(layer)

    if cy.OutlineCount() == 0:
        continue

    bbox = cy.BBox()
    rows.append([
        fp.GetReference(),
        fp.GetValue(),
        fp.GetFPIDAsString(),
        round(pcbnew.ToMils(bbox.GetWidth()), 2),
        round(pcbnew.ToMils(bbox.GetHeight()), 2),
        round(cy.Area() / scale, 2)
    ])

rows.sort(key=lambda row: row[5], reverse=True)

path = os.path.join(
    os.path.dirname(board.GetFileName()),
    "component_areas.csv"
)

with open(path, "w", newline="") as file:
    writer = csv.writer(file)
    writer.writerow(["Ref", "Value", "Footprint", "Width_mil",
                 "Height_mil", "Area_mil2"])
    writer.writerows(rows)

print("Total courtyard area:", round(sum(r[5] for r in rows), 2), "mil²")
print("Saved:", path)
