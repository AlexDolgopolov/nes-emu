OPCODE_TABLE = {
    # --- Load/Store Operations ---
    0xA9: ("LDA", "Immediate"), 0xA5: ("LDA", "ZeroPage"), 0xB5: ("LDA", "ZeroPage,X"), 0xAD: ("LDA", "Absolute"), 0xBD: ("LDA", "Absolute,X"), 0xB9: ("LDA", "Absolute,Y"), 0xA1: ("LDA", "(Indirect,X)"), 0xB1: ("LDA", "(Indirect),Y"),
    0xA2: ("LDX", "Immediate"), 0xA6: ("LDX", "ZeroPage"), 0xB6: ("LDX", "ZeroPage,Y"), 0xAE: ("LDX", "Absolute"), 0xBE: ("LDX", "Absolute,Y"),
    0xA0: ("LDY", "Immediate"), 0xA4: ("LDY", "ZeroPage"), 0xB4: ("LDY", "ZeroPage,X"), 0xAC: ("LDY", "Absolute"), 0xBC: ("LDY", "Absolute,X"),
    0x85: ("STA", "ZeroPage"), 0x95: ("STA", "ZeroPage,X"), 0x8D: ("STA", "Absolute"), 0x9D: ("STA", "Absolute,X"), 0x99: ("STA", "Absolute,Y"), 0x81: ("STA", "(Indirect,X)"), 0x91: ("STA", "(Indirect),Y"),
    0x86: ("STX", "ZeroPage"), 0x96: ("STX", "ZeroPage,Y"), 0x8E: ("STX", "Absolute"),
    0x84: ("STY", "ZeroPage"), 0x94: ("STY", "ZeroPage,X"), 0x8C: ("STY", "Absolute"),

    # --- Register Transfers ---
    0xAA: ("TAX", "Implied"), 0xA8: ("TAY", "Implied"), 0xBA: ("TSX", "Implied"), 0x8A: ("TXA", "Implied"), 0x9A: ("TXS", "Implied"), 0x98: ("TYA", "Implied"),

    # --- Stack Operations ---
    0x48: ("PHA", "Implied"), 0x08: ("PHP", "Implied"), 0x68: ("PLA", "Implied"), 0x28: ("PLP", "Implied"),

    # --- Logical Operations ---
    0x29: ("AND", "Immediate"), 0x25: ("AND", "ZeroPage"), 0x35: ("AND", "ZeroPage,X"), 0x2D: ("AND", "Absolute"), 0x3D: ("AND", "Absolute,X"), 0x39: ("AND", "Absolute,Y"), 0x21: ("AND", "(Indirect,X)"), 0x31: ("AND", "(Indirect),Y"),
    0x49: ("EOR", "Immediate"), 0x45: ("EOR", "ZeroPage"), 0x55: ("EOR", "ZeroPage,X"), 0x4D: ("EOR", "Absolute"), 0x5D: ("EOR", "Absolute,X"), 0x59: ("EOR", "Absolute,Y"), 0x41: ("EOR", "(Indirect,X)"), 0x51: ("EOR", "(Indirect),Y"),
    0x09: ("ORA", "Immediate"), 0x05: ("ORA", "ZeroPage"), 0x15: ("ORA", "ZeroPage,X"), 0x0D: ("ORA", "Absolute"), 0x1D: ("ORA", "Absolute,X"), 0x19: ("ORA", "Absolute,Y"), 0x01: ("ORA", "(Indirect,X)"), 0x11: ("ORA", "(Indirect),Y"),
    0x24: ("BIT", "ZeroPage"), 0x2C: ("BIT", "Absolute"),

    # --- Arithmetic Operations ---
    0x69: ("ADC", "Immediate"), 0x65: ("ADC", "ZeroPage"), 0x75: ("ADC", "ZeroPage,X"), 0x6D: ("ADC", "Absolute"), 0x7D: ("ADC", "Absolute,X"), 0x79: ("ADC", "Absolute,Y"), 0x61: ("ADC", "(Indirect,X)"), 0x71: ("ADC", "(Indirect),Y"),
    0xE9: ("SBC", "Immediate"), 0xE5: ("SBC", "ZeroPage"), 0xF5: ("SBC", "ZeroPage,X"), 0xED: ("SBC", "Absolute"), 0xFD: ("SBC", "Absolute,X"), 0xF9: ("SBC", "Absolute,Y"), 0xE1: ("SBC", "(Indirect,X)"), 0xF1: ("SBC", "(Indirect),Y"),
    0xC9: ("CMP", "Immediate"), 0xC5: ("CMP", "ZeroPage"), 0xD5: ("CMP", "ZeroPage,X"), 0xCD: ("CMP", "Absolute"), 0xDD: ("CMP", "Absolute,X"), 0xD9: ("CMP", "Absolute,Y"), 0xC1: ("CMP", "(Indirect,X)"), 0xD1: ("CMP", "(Indirect),Y"),
    0xE0: ("CPX", "Immediate"), 0xE4: ("CPX", "ZeroPage"), 0xEC: ("CPX", "Absolute"),
    0xC0: ("CPY", "Immediate"), 0xC4: ("CPY", "ZeroPage"), 0xCC: ("CPY", "Absolute"),

    # --- Increments & Decrements ---
    0xE6: ("INC", "ZeroPage"), 0xF6: ("INC", "ZeroPage,X"), 0xEE: ("INC", "Absolute"), 0xFE: ("INC", "Absolute,X"),
    0xE8: ("INX", "Implied"), 0xC8: ("INY", "Implied"),
    0xC6: ("DEC", "ZeroPage"), 0xD6: ("DEC", "ZeroPage,X"), 0xCE: ("DEC", "Absolute"), 0xDE: ("DEC", "Absolute,X"),
    0xCA: ("DEX", "Implied"), 0x88: ("DEY", "Implied"),

    # --- Shifts ---
    0x0A: ("ASL", "Accumulator"), 0x06: ("ASL", "ZeroPage"), 0x16: ("ASL", "ZeroPage,X"), 0x0E: ("ASL", "Absolute"), 0x1E: ("ASL", "Absolute,X"),
    0x4A: ("LSR", "Accumulator"), 0x46: ("LSR", "ZeroPage"), 0x56: ("LSR", "ZeroPage,X"), 0x4E: ("LSR", "Absolute"), 0x5E: ("LSR", "Absolute,X"),
    0x2A: ("ROL", "Accumulator"), 0x26: ("ROL", "ZeroPage"), 0x36: ("ROL", "ZeroPage,X"), 0x2E: ("ROL", "Absolute"), 0x3E: ("ROL", "Absolute,X"),
    0x6A: ("ROR", "Accumulator"), 0x66: ("ROR", "ZeroPage"), 0x76: ("ROR", "ZeroPage,X"), 0x6E: ("ROR", "Absolute"), 0x7E: ("ROR", "Absolute,X"),

    # --- Jumps & Calls ---
    0x4C: ("JMP", "Absolute"), 0x6C: ("JMP", "Indirect"),
    0x20: ("JSR", "Absolute"), 0x60: ("RTS", "Implied"),

    # --- Branches ---
    0x90: ("BCC", "Relative"), 0xB0: ("BCS", "Relative"), 0xF0: ("BEQ", "Relative"), 0x30: ("BMI", "Relative"), 0xD0: ("BNE", "Relative"), 0x10: ("BPL", "Relative"), 0x50: ("BVC", "Relative"), 0x70: ("BVS", "Relative"),

    # --- Status Flag Changes ---
    0x18: ("CLC", "Implied"), 0xD8: ("CLD", "Implied"), 0x58: ("CLI", "Implied"), 0xB8: ("CLV", "Implied"),
    0x38: ("SEC", "Implied"), 0xF8: ("SED", "Implied"), 0x78: ("SEI", "Implied"),

    # --- System Functions ---
    0x00: ("BRK", "Implied"), 0xEA: ("NOP", "Implied"), 0x40: ("RTI", "Implied"),
}
from rich.console import Console
from rich.table import Table
from rich.text import Text
from rich.panel import Panel
from rich import box

def print_summary(initial: dict, expected: dict, actual: dict, opcode_raw: str, external_info: str = ""):
    console = Console()
    
    # 1. Декодирование опкода
    bytes_list = opcode_raw.split()
    main_opcode = int(bytes_list[0], 16) if bytes_list else 0
    instr_name, addr_mode = OPCODE_TABLE.get(main_opcode, ("UNKNOWN", "???"))
    
    # 2. Заголовок
    header_text = f"[bold yellow]Instruction:[/bold yellow] {instr_name} ({addr_mode}) | [bold cyan]Bytes:[/bold cyan] {opcode_raw}"
    console.print(Panel(header_text, border_style="blue", title="NES CPU Step Info"))

    # 3. Таблица состояния (Регистры и RAM)
    state_table = Table(
        show_header=True, 
        header_style="bold magenta", 
        expand=True, 
        box=box.SIMPLE_HEAD
    )
    
    state_table.add_column("Register", justify="center", style="bold white")
    state_table.add_column("Initial", justify="right")
    state_table.add_column("Expected", justify="right")
    state_table.add_column("Actual", justify="right")
    state_table.add_column("Status", justify="center")

    regs = ['pc', 's', 'a', 'x', 'y', 'p']
    for reg in regs:
        i_v, e_v, a_v = initial.get(reg, 0), expected.get(reg, 0), actual.get(reg, 0)
        fmt = "04X" if reg == 'pc' else "02X"
        
        is_match = (e_v == a_v)
        match_style = "green" if is_match else "bold red"
        status = "[green]OK[/green]" if is_match else "[bold red]FAIL[/bold red]"
        
        state_table.add_row(
            reg.upper(), 
            f"0x{i_v:{fmt}}", 
            f"0x{e_v:{fmt}}", 
            Text(f"0x{a_v:{fmt}}", style=match_style),
            status
        )

    # Добавляем RAM, если она есть
    def get_ram_map(data):
        return {addr: val for addr, val in data.get('ram', [])}

    i_ram, e_ram, a_ram = get_ram_map(initial), get_ram_map(expected), get_ram_map(actual)
    all_addrs = sorted(set(i_ram.keys()) | set(e_ram.keys()) | set(a_ram.keys()))

    if all_addrs:
        state_table.add_section()
        for addr in all_addrs:
            iv, ev, av = i_ram.get(addr, 0), e_ram.get(addr, 0), a_ram.get(addr, 0)
            is_match = (ev == av)
            state_table.add_row(
                f"RAM[0x{addr:04X}]", f"0x{iv:02X}", f"0x{ev:02X}", 
                Text(f"0x{av:02X}", style="green" if is_match else "bold red"),
                "[green]OK[/green]" if is_match else "[bold yellow]DIFF[/bold yellow]"
            )

    console.print(state_table)

    # 4. Вывод дополнительной информации в отдельном блоке
    if external_info:
        # Используем Panel для красивого обрамления многострочного текста
        info_panel = Panel(
            Text(external_info, style="italic cyan"),
            title="External CPU Information",
            title_align="left",
            border_style="dim cyan",
            box=box.SQUARE
        )
        console.print(info_panel)
    
    # 5. Вердикт
    if not all(expected.get(r) == actual.get(r) for r in regs):
        console.print("[bold red]❌ STATE MISMATCH DETECTED![/bold red]\n")
    else:
        console.print("[bold green]✅ STEP OK[/bold green]\n")