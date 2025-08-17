# Project Structure

## Current Directory Layout
```
.
├── .kiro/                          # Kiro IDE configuration
│   ├── hooks/                      # Automated development hooks
│   │   ├── code-quality-check.json # Code quality automation
│   │   └── docs-sync-hook.kiro.hook # Documentation sync
│   ├── specs/                      # Project specifications
│   │   └── c-programming-lessons/  # Curriculum specifications
│   └── steering/                   # AI assistant guidance documents
│       ├── product.md              # Product overview and purpose
│       ├── tech.md                 # Technology stack information
│       └── structure.md            # This file
├── c-programming-lessons/          # Main curriculum content
│   ├── basics/                     # Foundation level (6 lessons)
│   │   ├── lesson-01-hello-world/
│   │   ├── lesson-02-variables-types/
│   │   ├── lesson-03-operators/
│   │   ├── lesson-04-control-structures/
│   │   ├── lesson-05-loops/
│   │   └── lesson-06-functions/
│   ├── intermediate/               # Intermediate level (6 lessons)
│   │   ├── lesson-01-pointers/
│   │   ├── lesson-02-arrays-strings/
│   │   ├── lesson-03-advanced-functions/
│   │   ├── lesson-04-scope-storage/
│   │   ├── lesson-05-preprocessor/
│   │   └── lesson-06-file-io/
│   ├── pro/                        # Advanced level (6 lessons)
│   │   ├── lesson-01-structures-unions/
│   │   ├── lesson-02-dynamic-memory/
│   │   ├── lesson-03-advanced-file-handling/
│   │   ├── lesson-04-data-structures/
│   │   ├── lesson-05-function-pointers/
│   │   └── lesson-06-multi-file-projects/
│   ├── master/                     # Expert level (6 lessons)
│   │   ├── lesson-01-advanced-algorithms/
│   │   ├── lesson-02-system-programming/
│   │   ├── lesson-03-memory-optimization/
│   │   ├── lesson-04-bit-manipulation/
│   │   ├── lesson-05-advanced-debugging/
│   │   └── lesson-06-performance-analysis/
│   ├── templates/                  # Lesson templates and scaffolding
│   ├── README.md                   # Curriculum overview
│   ├── LESSON_INDEX.md            # Complete lesson navigation
│   ├── LEARNING_GUIDE.md          # Learning strategies and tips
│   ├── test_config.json           # Testing configuration
│   └── [validation scripts]       # Quality assurance tools
├── test-hooks.md                   # Hook testing documentation
└── README.md                       # Main project documentation
```

## Lesson Structure Standards

Each lesson follows a consistent organization:
```
lesson-XX-topic-name/
├── main.c          # Primary source code with comprehensive examples
├── README.md       # Detailed lesson documentation and explanations
├── Makefile        # Standardized build configuration
└── [additional files as needed - headers, data files, etc.]
```

### Lesson Components
- **main.c**: Complete, compilable C code demonstrating concepts
- **README.md**: Comprehensive documentation including:
  - Learning objectives and key concepts
  - Code explanations and best practices
  - Compilation and execution instructions
  - Practice exercises and next steps
- **Makefile**: Standardized build system with common targets
- **Additional Files**: Headers, configuration, or data files as needed

## Configuration Management

### Kiro IDE Integration
- **`.kiro/hooks/`**: Automated development workflow tools
  - `code-quality-check.json`: Comprehensive code quality validation
  - `docs-sync-hook.kiro.hook`: Documentation synchronization
- **`.kiro/specs/`**: Project specifications and requirements
- **`.kiro/steering/`**: AI assistant guidance and project context

### Quality Assurance
- **Validation Scripts**: Python-based testing and validation tools
- **Test Configuration**: Standardized testing parameters and expectations
- **Build System**: Consistent Makefile structure across all lessons

## Organization Principles

### Hierarchical Learning Structure
- **Progressive Difficulty**: Each level builds on previous knowledge
- **Consistent Naming**: Predictable lesson numbering and topic naming
- **Modular Design**: Each lesson is self-contained but part of larger curriculum

### Documentation Standards
- **Comprehensive Coverage**: Every lesson includes detailed documentation
- **Consistent Format**: Standardized README structure across all lessons
- **Cross-References**: Links between related lessons and concepts

### Code Quality Standards
- **Compilation**: All code compiles without errors or warnings
- **Style**: Consistent C programming conventions and formatting
- **Comments**: Comprehensive inline documentation and explanations
- **Examples**: Complete, working examples for every concept

### Maintenance Guidelines
- **Version Control**: Track changes to curriculum and individual lessons
- **Testing**: Automated validation of all code and documentation
- **Updates**: Regular review and improvement of content
- **Consistency**: Maintain standards across all lessons and levels

## Extensibility Considerations
- **Template System**: Standardized templates for adding new lessons
- **Modular Architecture**: Easy to modify or extend individual lessons
- **Scalable Organization**: Structure supports additional levels or topics
- **Tool Integration**: Hooks and automation support development workflow